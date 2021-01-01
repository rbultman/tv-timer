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
#include "rtcClock32khz.h"
#include "Screen_Time.h"
#include "Screen_SetDate.h"
#include "Screen_SetTime.h"
#include "Screen_Start.h"
#include "Screen_Timer.h"

DigitalOut redLed(LED1);
DigitalOut greenLed(LED2);
DigitalOut blueLed(LED3);
DigitalOut redLed2(LED4);

SPI spi(D11, NC, D13, D10);
Ds3231 rtc(D14, D15);

static volatile uint32_t seconds = 0;
static bool timeIsInitialized = false;

static Screen_Time screen_time;
static Screen_SetDate screen_setDate;
static Screen_SetDate screen_setDateInitial;
static Screen_SetTime screen_setTime;
static Screen_Start screen_start;
static Screen_Timer screen_timer;

static Thread heartbeatThread;
static void HeartbeatTask()
{
   while(true)
   {
      ds3231_time_t time;
      rtc.get_time(&time);
      ds3231_calendar_t date;
      rtc.get_calendar(&date);
      screen_time.UpdateScreen(
         time.hours, 
         time.minutes, 
         time.seconds, 
         time.am_pm,
         date.month, 
         date.date, 
         date.year);
      time_t currentEpoch = rtc.get_epoch();
      ds3231_alrm_t alarm1;
      rtc.get_alarm(&alarm1, 1);
      screen_timer.UpdateScreen(currentEpoch, alarm1);

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

   if (timeIsInitialized)
   {
      screen_setDate.GetDate(&month, &day, &year);
   }
   else
   {
      screen_setDateInitial.GetDate(&month, &day, &year);
   }
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
   if (whichButton == Screen_NextButtonPressed)
   {
      InitClock();
      timeIsInitialized = true;
      screen_time.LoadScreen();
   }
   else
   {
      if (timeIsInitialized)
      {
         screen_setDate.LoadScreen();
      }
      else
      {
         screen_setDateInitial.LoadScreen();
      }
   }
}

void SetDateButtonCallback(uint8_t whichButton)
{
   ds3231_time_t time;

   if (whichButton == Screen_NextButtonPressed)
   {
      rtc.get_time(&time);
      screen_setTime.SetTime(time.hours, time.minutes, time.am_pm);
      screen_setTime.LoadScreen();
   }
   else
   {
      screen_time.LoadScreen();
   }
}

void TimeScreenCallback (uint8_t whichButton)
{
   screen_start.LoadScreen();
}

void TimerScreenCallback(uint8_t whichButton)
{
}

void StartScreenCallback(uint8_t whichButton)
{
   ds3231_calendar_t date;
   time_t t;
   struct tm ts;
   ds3231_alrm_t a;
   
   switch (whichButton)
   {
      case Screen_PreviousButtonPressed:
         screen_time.LoadScreen();
         break;
      case Screen_Menu1Pressed:
         t = rtc.get_epoch() + 7200;
         ts = *localtime(&t);
         a.date = ts.tm_mday;
         a.hours = ts.tm_hour;
         a.minutes = ts.tm_min;
         a.seconds = ts.tm_sec;
         a.dy_dt = 0; 
         a.am1 = a.am2 = a.am3 = a.am4 = 0;
         a.mode = 0;
         a.day = ts.tm_wday + 1;
         rtc.set_alarm(a, 1);
         screen_timer.LoadScreen();
         break;
      case Screen_Menu2Pressed:
         puts("Settings button pressed.");
         rtc.get_calendar(&date);
         screen_setDate.SetDate(date.month-1, date.date, date.year);
         screen_setDate.LoadScreen();
         break;
      }
}

int main()
{
   printf("Starting...\r\n");

   spi.frequency(10000000);

   lcdBacklight = 1;

   Display_Initialize();

   screen_time.CreateScreen(Display_GetInputDevice(), false, false);
   screen_time.RegisterButtonPressedCallback(TimeScreenCallback);

   screen_timer.CreateScreen(Display_GetInputDevice(), false, false);
   screen_timer.RegisterButtonPressedCallback(TimerScreenCallback);

   screen_start.CreateScreen(Display_GetInputDevice());
   screen_start.RegisterButtonPressedCallback(StartScreenCallback);

   screen_setDateInitial.CreateScreen(Display_GetInputDevice(), true, false);
   screen_setDateInitial.RegisterButtonPressedCallback(SetDateButtonCallback);
   screen_setDateInitial.SetDate(11, 18, 22);

   screen_setDate.CreateScreen(Display_GetInputDevice(), true, true);
   screen_setDate.RegisterButtonPressedCallback(SetDateButtonCallback);
   screen_setDate.SetDate(11, 18, 22);

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
      timeIsInitialized = true;
      screen_time.LoadScreen();
   }

   heartbeatThread.start(HeartbeatTask);
   InitRtcClock32khzInput(RtcClock32khzInputInterruptHandler);

   while (true)
   {
      ThisThread::sleep_for(33ms);
   }
}
