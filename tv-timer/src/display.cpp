/*
    display.cpp

    A wrapper and interface file for the display and encoder

    Author: Rob Bultman
    License: MIT
*/

#include <Encoder.h>
#include <TeensyThreads.h>
#include "display.h"
#include "ST7565.h"
#include "io_ports.h"

static lv_disp_drv_t displayDriver;
static lv_disp_t *pDisplayDevice;
static lv_disp_buf_t displayBuffer;
static lv_color_t buf_1[LV_HOR_RES_MAX * 10];
static lv_color_t buf_2[LV_HOR_RES_MAX * 10];

Bounce encoderButton(ENCODER_BUTTON, 50);
#define ENCODER_CENTER 16384
static Encoder encoder(2, 3);

static lv_indev_drv_t indev_drv;
static lv_indev_t *pInputDevice;

static void initializeEncoder()
{
  encoder.write(ENCODER_CENTER);
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
    delay(100);
    lcdReset = 1;
    delay(100);
    for (i = 0; i < sizeof(initCmds) / sizeof(uint8_t); i++)
    {
        lcdDC = 0;
        SPI.transfer(initCmds[i]);
    }
}

static void lvglTick()
{
  while (true)
  {
    delay(5);
    lv_tick_inc(5);
  }
}

static void lvglTask()
{
  while (true)
  {
    delay(5);
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
static void encoderButtonThread()
{
  while(true)
  {
    if (encoderButton.update())
    {
      if (encoderButton.risingEdge())
      {
        
      }
      else if (encoderButton.fallingEdge())
      {
        
      }
    }
  }
}

static bool encoder_read(lv_indev_drv_t *drv, lv_indev_data_t *data)
{
  int16_t encSteps = encoder.read();

  data->enc_diff = 0;

  if (encSteps / 4 != 0)
  {
    data->enc_diff = encSteps / 4;
    encoder.write(ENCODER_CENTER);
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

    threads.addThread(lvglTick);
    threads.addThread(lvglTask);

    delay(1000);

    encoderButton.fall(EncoderButtonDownHandler);
    encoderButton.rise(EncoderButtonUpHandler);
}

lv_indev_t * Display_GetInputDevice()
{
    return pInputDevice;
}
