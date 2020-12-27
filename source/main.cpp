/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "mbed.h"
#include "io_ports.h"
#include "lvgl.h"
#include "ST7565.h"
#include "ds3231/ds3231.h"
#include "system_RZ_A1H.h"
#include "iodefine.h"
#include "mtu2_iobitmask.h"
extern "C" 
{
   #include "irq_ctrl.h"
}
#include "menu_test.h"

DigitalOut redLed(LED1);
DigitalOut greenLed(LED2);
DigitalOut blueLed(LED3);
DigitalOut redLed2(LED4);
InterruptIn encoderButton(ENCODER_BUTTON);
#define ENCODER_CENTER 16384

SPI spi(D11, NC, D13, D10);
Ds3231 rtc(D14, D15);

static lv_indev_drv_t indev_drv;
static lv_indev_t *pInputDevice;

static lv_disp_drv_t displayDriver;
static lv_disp_t *pDisplayDevice;
static lv_disp_buf_t displayBuffer;
static lv_color_t buf_1[LV_HOR_RES_MAX * 10];
static lv_color_t buf_2[LV_HOR_RES_MAX * 10];

static volatile uint32_t seconds = 0;

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

void RtcClockInputInterrupt();
static Thread heartbeatThread;
static void HeartbeatTask()
{
   while(true)
   {
      greenLed = 1;
      ThisThread::sleep_for(50ms);
      // printf("Seconds: %lu\r\n", seconds);

      greenLed = 0;
      ThisThread::sleep_for(950ms);
   }
}

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

void RtcClockInputInterrupt()
{
   MTU2.TSR_2 = MTU2.TSR_2 & ~MTU2_TSR_n_TGFA;
   seconds++;
}

DigitalIn rtcClockInput(P1_1, PullUp);
void InitRtcClockInput()
{
   // Enable clock to MTU2
   CPG.STBCR3 = CPG.STBCR3 & ~CPG_STBCR3_BIT_MSTP33;
   // Set Channel 2 TCNT input to TCLKC, reset by TGRA
   MTU2.TCR_2 = 0x26;
   // Reset TGRA after 1 second
   MTU2.TGRA_2 = 32768;
   // use alternate pin function
   GPIO.PIPC1 = GPIO.PIPC1 | 0x0002;
   // set P1_1 to alt mode 3
   GPIO.PFCAE1 = GPIO.PFCAE1 & ~0x0002;
   GPIO.PFCE1 = GPIO.PFCE1 | 0x0002;
   GPIO.PFC1 = GPIO.PFC1 & ~0x0002;
   GPIO.PMC1 = GPIO.PMC1 | 0x0002;
   // Install the interrupt handler
   uint32_t retval = InterruptHandlerRegister(TGI2A_IRQn, RtcClockInputInterrupt);
   if (retval == 0)
   {
      puts("IRQ for RTC clock successfully installed.");
   }
   else
   {
      puts("ERROR installing IRQ for RTC clock.");
   }
   // Enable the interrupt in MTU2
   MTU2.TIER_2 = MTU2.TIER_2 | MTU2_TIER_n_TGIEA;
   // Enable the IRQ at the core
   IRQ_Enable(TGI2A_IRQn);
   // start the timer
   MTU2.TSTR = MTU2.TSTR | 0x04;
}

static void InitClock()
{
   ds3231_time_t rtc_time;
   ds3231_calendar_t rtc_calendar;
   ds3231_cntl_stat_t rtc_control_status = {0, 0x08};

   rtc.set_cntl_stat_reg(rtc_control_status);
   rtc_calendar.day = 6;
   rtc_calendar.date = 25;
   rtc_calendar.month = 12;
   rtc_calendar.year = 20;
   rtc_time.mode = 1; // 12 hour mode
   rtc_time.am_pm = 1;
   rtc_time.hours = 1;
   rtc_time.minutes = 14;
   rtc_time.seconds = 0;

   //Set the time, uses inverted logic for return value
   if (rtc.set_time(rtc_time))
   {
      printf("\nrtc.set_time failed!!\n");
   }
   else
   {
      puts("RTC time set success.");
   }

   //Set the calendar, uses inverted logic for return value
   if (rtc.set_calendar(rtc_calendar))
   {
      printf("\nrtc.set_calendar failed!!\n");
   }
   else
   {
      puts("RTC date set success.");
   }
}

bool encoderButtonPressed = false;
void EncoderButtonDownHandler()
{
   encoderButtonPressed = true;
}

void EncoderButtonUpHandler()
{
   encoderButtonPressed = false;
}

bool encoder_read(lv_indev_drv_t *drv, lv_indev_data_t *data)
{
   int16_t encSteps = MTU2.TCNT_1 - ENCODER_CENTER;

   data->enc_diff = 0;

   if (encSteps/4 != 0)
   {
      data->enc_diff = encSteps/4;
      MTU2.TCNT_1 = ENCODER_CENTER;
   }

   data->state = encoderButtonPressed ? LV_INDEV_STATE_PR :
         LV_INDEV_STATE_REL;

         return false;
}

int main()
{
   printf("Starting...\r\n");

   initializeEncoder();
   InitClock();

   spi.frequency(10000000);

   lv_init();
   st7565_init();
   initLCD();

   lcdBacklight = 1;

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

   heartbeatThread.start(HeartbeatTask);
   InitRtcClockInput();

   encoderButton.fall(EncoderButtonDownHandler);
   encoderButton.rise(EncoderButtonUpHandler);

   lv_scr_load(MenuTest_CreateScreen(pInputDevice));
   char msg[64] = "Menu";
   MenuTest_ShowMenu(msg);

   while (true)
   {
      ThisThread::sleep_for(33ms);
   }
}
