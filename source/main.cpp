/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
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
#include "Screen_Time.h"
#include "Screen_SetDate.h"
#include "Screen_SetTime.h"
#include "SDBlockDevice.h"
#include "FATFileSystem.h"
#include "rtcClock32khz.h"

DigitalOut redLed(LED1);
DigitalOut greenLed(LED2);
DigitalOut blueLed(LED3);
DigitalOut redLed2(LED4);

SPI spi(D11, NC, D13, D10);
Ds3231 rtc(D14, D15);

static volatile uint32_t seconds = 0;

Screen_Time screen_time;
Screen_SetDate screen_setDate;
Screen_SetDate screen_setDateInitial;
Screen_SetTime screen_setTime;
//Menu_Test menu_test;

static Thread heartbeatThread;
static void HeartbeatTask()
{
   while(true)
   {
      ds3231_time_t time;
      rtc.get_time(&time);
      ds3231_calendar_t date;
      rtc.get_calendar(&date);
      screen_time.UpdateScreen(time.hours, time.minutes, time.seconds, date.month, date.date, date.year);

      greenLed = 1;
      ThisThread::sleep_for(50ms);

      greenLed = 0;
      ThisThread::sleep_for(950ms);
   }
}

void RtcClock32khzInputInterruptHandler()
{
   MTU2.TSR_2 = MTU2.TSR_2 & ~MTU2_TSR_n_TGFA;
   seconds++;
}

static void InitClock()
{
   ds3231_time_t rtc_time;
   ds3231_calendar_t rtc_calendar;
   ds3231_cntl_stat_t rtc_control_status = {0, 0x08};
   struct tm time;
   struct tm *pTimeConverted;
   time_t rawTime;
   uint8_t hours;
   uint8_t minutes;
   uint8_t amPm;
   uint8_t month;
   uint8_t day;
   uint8_t year;

   rtc.set_cntl_stat_reg(rtc_control_status);
   rtc_calendar.day = 6;
   rtc_time.mode = 1; // 12 hour mode

   screen_setDateInitial.GetDate(&month, &day, &year);
   screen_setTime.GetTime(&hours, &minutes, &amPm);

   rtc_calendar.date = day;
   rtc_calendar.month = month + 1;
   rtc_calendar.year = year;
   rtc_time.hours = hours;
   rtc_time.minutes = minutes;
   rtc_time.seconds = 0;
   rtc_time.am_pm = amPm;

   time.tm_year = year + 100;
   time.tm_mon = month;
   time.tm_mday = day;

   time.tm_hour = hours;
   if (amPm)
   {
      time.tm_hour = 24 - hours;
   }
   
   time.tm_min = minutes;
   time.tm_sec = 0;
   
   rawTime = mktime(&time);
   pTimeConverted = localtime(&rawTime);

   rtc_calendar.day = pTimeConverted->tm_wday + 1;

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

void SetTimeButtonCallback(uint8_t whichButton)
{
   uint8_t hours;
   uint8_t minutes;
   uint8_t amPm;

   screen_setTime.GetTime(&hours, &minutes, &amPm);

   if (whichButton == Screen_NextButtonPressed)
   {
      puts("Next button pressed.");
      InitClock();
      screen_time.LoadScreen();
   }
   else
   {
      puts("Previous button pressed.");
      screen_setDateInitial.LoadScreen();
   }

   printf("Time is now: %d:%02d %s\r\n", hours, minutes, amPm ? "PM" : "AM");
}

void SetDateButtonCallback(uint8_t whichButton)
{
   uint8_t month;
   uint8_t day;
   uint8_t year;

   screen_setDateInitial.GetDate(&month, &day, &year);

   if (whichButton == Screen_NextButtonPressed)
   {
      screen_setTime.LoadScreen();
   }
   else
   {
      puts("Previous button pressed.");
   }

   printf("Date is now: %d/%d/%d\r\n", month, day, year + 2000);
}

int main()
{
   printf("Starting...\r\n");

   spi.frequency(10000000);

   lcdBacklight = 1;

   Display_Initialize();

   screen_time.CreateScreen(Display_GetInputDevice(), false, false);

   screen_setDateInitial.CreateScreen(Display_GetInputDevice(), true, false);
   screen_setDateInitial.RegisterButtonPressedCallback(SetDateButtonCallback);
   screen_setDateInitial.SetDate(11, 18, 22);

   screen_setTime.CreateScreen(Display_GetInputDevice(), true, true);
   screen_setTime.RegisterButtonPressedCallback(SetTimeButtonCallback);
   screen_setTime.SetTime(12, 31, 0);

   ds3231_cntl_stat_t rtcStatus;
   rtc.get_cntl_stat_reg(&rtcStatus);
   printf("RTC control: %d\r\n", rtcStatus.control);
   printf("RTC status: %d\r\n", rtcStatus.status);
   if (rtcStatus.status & OSF)
   {
      puts("RTC oscillator stopped, need to get the time from the user");
      screen_setDateInitial.LoadScreen();
   }
   else
   {
      puts("RTC oscillator already configured.");
      screen_time.LoadScreen();
   }

   // lv_scr_load(menu_test.CreateScreen(Display_GetInputDevice()));
   // char msg[64] = "Menu";
   // menu_test.ShowMenu(msg);

   heartbeatThread.start(HeartbeatTask);
   InitRtcClock32khzInput(RtcClock32khzInputInterruptHandler);

   while (true)
   {
      ThisThread::sleep_for(33ms);
   }
}
