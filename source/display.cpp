/*
    display.cpp

    A wrapper and interface file for the display and encoder

    Author: Rob Bultman
    License: MIT
*/

#include "mbed.h"
#include "system_RZ_A1H.h"
#include "iodefine.h"
#include "mtu2_iobitmask.h"
extern "C"
{
#include "irq_ctrl.h"
}
#include "display.h"
#include "ST7565.h"
#include "io_ports.h"

static lv_disp_drv_t displayDriver;
static lv_disp_t *pDisplayDevice;
static lv_disp_buf_t displayBuffer;
static lv_color_t buf_1[LV_HOR_RES_MAX * 10];
static lv_color_t buf_2[LV_HOR_RES_MAX * 10];
InterruptIn encoderButton(ENCODER_BUTTON);
#define ENCODER_CENTER 16384
static lv_indev_drv_t indev_drv;
static lv_indev_t *pInputDevice;

static void initializeEncoder()
{
    // Set P1_0 and P1_10 to alt functions
    // Initialize MTU2
    // Enable clock to MTU2
    CPG.STBCR3 = CPG.STBCR3 & ~CPG_STBCR3_BIT_MSTP33;
    MTU2.TCNT_1 = ENCODER_CENTER;
    // set mode to phase counting
    MTU2.TMDR_1 = 0x04;

    uint16_t mask;
    mask = (1 << 10) | 1;
    GPIO.PIPC1 = GPIO.PIPC1 | mask;
    // set P1_0 to alt mode 3
    // set P1_10 to alt mode 4
    GPIO.PFCAE1 = GPIO.PFCAE1 & ~mask;
    GPIO.PFCE1 = GPIO.PFCE1 | mask;
    GPIO.PFC1 = GPIO.PFC1 | (1 << 10);
    GPIO.PMC1 = GPIO.PMC1 | mask;
    // start the timer
    MTU2.TSTR = MTU2.TSTR | 0x02;
}

static void initLCD()
{
    const uint8_t initCmds[] =
        {
            0xA0, // ADC select normal
            0xAE, // display off
            0xC0, // common output mode select normal
            0xA2, // LCD bias 1/9
            0x2F, // Internal power operating mode
            0x26, // select resistor ratio
            0x81, // Set V5 output voltage
            0x11, // Column addres set upper bit
            0xAF, // Display on
        };
    uint8_t i;
    lcdReset = 0;
    ThisThread::sleep_for(100ms);
    lcdReset = 1;
    ThisThread::sleep_for(100ms);
    for (i = 0; i < sizeof(initCmds) / sizeof(uint8_t); i++)
    {
        lcdDC = 0;
        spi.write(initCmds[i]);
    }
}

static Thread lvglTickThread;
static void lvglTick()
{
    while (true)
    {
        ThisThread::sleep_for(5ms);
        lv_tick_inc(5);
    }
}

static Thread lvglTaskThread;
static void lvglTask()
{
    while (true)
    {
        ThisThread::sleep_for(5ms);
        lv_task_handler();
    }
}

static bool encoderButtonPressed = false;
static void EncoderButtonDownHandler()
{
    encoderButtonPressed = true;
}

static void EncoderButtonUpHandler()
{
    encoderButtonPressed = false;
}

static bool encoder_read(lv_indev_drv_t *drv, lv_indev_data_t *data)
{
    int16_t encSteps = MTU2.TCNT_1 - ENCODER_CENTER;

    data->enc_diff = 0;

    if (encSteps / 4 != 0)
    {
        data->enc_diff = encSteps / 4;
        MTU2.TCNT_1 = ENCODER_CENTER;
    }

    data->state = encoderButtonPressed ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;

    return false;
}

void Display_Initialize(void)
{
    initializeEncoder();
    lv_init();
    st7565_init();
    initLCD();

    // create display driver
    lv_disp_buf_init(&displayBuffer, buf_1, buf_2, LV_HOR_RES_MAX * 10);
    lv_disp_drv_init(&displayDriver);
    displayDriver.buffer = &displayBuffer;
    displayDriver.flush_cb = st7565_flush;
    pDisplayDevice = lv_disp_drv_register(&displayDriver);

    // create input device driver
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_ENCODER;
    indev_drv.read_cb = encoder_read;
    pInputDevice = lv_indev_drv_register(&indev_drv);

    lvglTickThread.start(lvglTick);
    lvglTickThread.set_priority(osPriorityNormal1);

    lvglTaskThread.start(lvglTask);
    lvglTaskThread.set_priority(osPriorityNormal);

    ThisThread::sleep_for(1s);

    encoderButton.fall(EncoderButtonDownHandler);
    encoderButton.rise(EncoderButtonUpHandler);
}

lv_indev_t * Display_GetInputDevice()
{
    return pInputDevice;
}
