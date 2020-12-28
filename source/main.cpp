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
#include "ds3231/ds3231.h"
#include "system_RZ_A1H.h"
#include "iodefine.h"
#include "mtu2_iobitmask.h"
extern "C" 
{
   #include "irq_ctrl.h"
}
#include "display.h"
#include "menu_test.h"
#include "Menu_Time.h"

DigitalOut redLed(LED1);
DigitalOut greenLed(LED2);
DigitalOut blueLed(LED3);
DigitalOut redLed2(LED4);

SPI spi(D11, NC, D13, D10);
Ds3231 rtc(D14, D15);

static volatile uint32_t seconds = 0;

Menu_Time menu_time;

void RtcClockInputInterrupt();
static Thread heartbeatThread;
static void HeartbeatTask()
{
   while(true)
   {
      ds3231_time_t time;
      rtc.get_time(&time);
      ds3231_calendar_t date;
      rtc.get_calendar(&date);
      // MenuTime_UpdateScreen(time.hours, time.minutes, time.seconds, date.month, date.day, date.year);
      menu_time.UpdateScreen(time.hours, time.minutes, time.seconds, date.month, date.day, date.year);

      greenLed = 1;
      ThisThread::sleep_for(50ms);
      // printf("Seconds: %lu\r\n", seconds);

      greenLed = 0;
      ThisThread::sleep_for(950ms);

   }
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

int main()
{
   printf("Starting...\r\n");

   spi.frequency(10000000);

   ds3231_cntl_stat_t rtcStatus;
   rtc.get_cntl_stat_reg(&rtcStatus);
   printf("RTC control: %d\r\n", rtcStatus.control);
   printf("RTC status: %d\r\n", rtcStatus.status);
   if (rtcStatus.status & OSF)
   {
      puts("RTC oscillator stopped...configuring.");
      InitClock();
   }
   else
   {
      puts("RTC oscillator already configured.");
   }

   lcdBacklight = 1;
   Display_Initialize();

   // lv_scr_load(MenuTest_CreateScreen(Display_GetInputDevice()));
   // char msg[64] = "Menu";
   // MenuTest_ShowMenu(msg);

   lv_scr_load(menu_time.CreateScreen(Display_GetInputDevice()));

   heartbeatThread.start(HeartbeatTask);
   InitRtcClockInput();

   while (true)
   {
      ThisThread::sleep_for(33ms);
   }
}
