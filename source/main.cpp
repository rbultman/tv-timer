/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include <cstdint>
#include <cstdlib>
#include <cstdio>
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
#include "rtc.h"
#include "Screen_Time.h"
#include "Screen_SetDate.h"
#include "Screen_SetTime.h"
#include "Screen_Start.h"
#include "Screen_Timer.h"
#include "Screen_TimerMenu.h"
#include "Screen_TimerRecharge.h"

DigitalOut redLed(LED1);
DigitalOut greenLed(LED2);
DigitalOut blueLed(LED3);
DigitalOut redLed2(LED4);

SPI spi(D11, NC, D13, D10);

static volatile uint32_t seconds = 0;
static bool timeIsInitialized = false;

static Screen_Time screen_time;
static Screen_SetDate screen_setDate;
static Screen_SetDate screen_setDateInitial;
static Screen_SetTime screen_setTime;
static Screen_Start screen_start;
static Screen_Timer screen_timer;
static Screen_TimerMenu screen_timerMenu;
static Screen_TimerRecharge screen_timerRecharge;

static Thread heartbeatThread;
static void HeartbeatTask()
{
   ds3231_alrm_t alarm;
   ds3231_time_t time;
   ds3231_calendar_t date;

   while (true)
   {
      if (lv_scr_act() == screen_time.scr)
      {
         rtc.get_time(&time);
         rtc.get_calendar(&date);
         screen_time.UpdateScreen(
             time.hours,
             time.minutes,
             time.seconds,
             time.am_pm,
             date.month,
             date.date,
             date.year);
      }

      if (lv_scr_act() == screen_timer.scr)
      {
         rtc.get_alarm(&alarm, ALARM1);
         screen_timer.UpdateScreen(rtc.get_epoch(), alarm);
      }

      if (lv_scr_act() == screen_timerRecharge.scr)
      {
         rtc.get_alarm(&alarm, ALARM2);
         screen_timerRecharge.UpdateScreen(rtc.get_epoch(), alarm);
      }

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

void SetTimeButtonCallback(uint8_t whichButton)
{
   uint8_t hours;
   uint8_t minutes;
   uint8_t amPm;
   uint8_t month;
   uint8_t day;
   uint8_t year;

   if (whichButton == Screen_NextButtonPressed)
   {
      if (timeIsInitialized)
      {
         screen_setDate.GetDate(&month, &day, &year);
      }
      else
      {
         screen_setDateInitial.GetDate(&month, &day, &year);
      }
      screen_setTime.GetTime(&hours, &minutes, &amPm);

      UpdateRtc(hours, minutes, 0, amPm, month, day, year);
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

void TimeScreenCallback(uint8_t whichButton)
{
   screen_start.LoadScreen();
}

void TimerScreenCallback(uint8_t whichButton)
{
   screen_timerMenu.LoadScreen();
}

void TimerMenuScreenCallback(uint8_t whichButton)
{
   ds3231_alrm_t alarm;
   time_t timeEpoch;
   time_t alarmEpoch;
   time_t timeRemaining;
   struct tm alarmTs;

   switch (whichButton)
   {
   case Screen_Menu1Pressed:
      // get current alarm epoch
      rtc.get_alarm(&alarm, ALARM1);
      AlarmToTimeStruct(alarmTs, alarm);
      alarmEpoch = mktime(&alarmTs);
      // get epoch for new alarm time
      timeEpoch = rtc.get_epoch();
      timeRemaining = 7200 - (alarmEpoch - timeEpoch);
      alarmEpoch = timeEpoch + timeRemaining;
      // create the alarm structure and set the alarm
      alarmTs = *localtime(&alarmEpoch);
      InitializeAlarm(alarm, alarmTs);
      rtc.set_alarm(alarm, ALARM2);

      EnableRtcInterrupt(ALARM2);
      DisableRtcInterrupt(ALARM1);
      ClearRtcFlags();

      screen_timerRecharge.UpdateScreen(rtc.get_epoch(), alarm);
      screen_timerRecharge.LoadScreen();
      break;
   case Screen_PreviousButtonPressed:
      screen_timer.LoadScreen();
   }
}

void TimerRechargeScreenCallback(uint8_t whichButton)
{
   switch (whichButton)
   {
   case Screen_TimeoutComplete:
      screen_time.LoadScreen();
      break;
   }
}

void StartScreenCallback(uint8_t whichButton)
{
   ds3231_calendar_t date;
   time_t timeEpoch;
   struct tm ts;
   ds3231_alrm_t alarm;

   switch (whichButton)
   {
   case Screen_PreviousButtonPressed:
      screen_time.LoadScreen();
      break;
   case Screen_Menu1Pressed:
      timeEpoch = rtc.get_epoch() + 7200;
      ts = *localtime(&timeEpoch);
      InitializeAlarm(alarm, ts);
      rtc.set_alarm(alarm, ALARM1);
      EnableRtcInterrupt(ALARM1);
      DisableRtcInterrupt(ALARM2);
      ClearRtcFlags();
      screen_timer.UpdateScreen(rtc.get_epoch(), alarm);
      screen_timer.LoadScreen();
      break;
   case Screen_Menu2Pressed:
      rtc.get_calendar(&date);
      screen_setDate.SetDate(date.month - 1, date.date, date.year);
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

   screen_timerMenu.CreateScreen(Display_GetInputDevice());
   screen_timerMenu.RegisterButtonPressedCallback(TimerMenuScreenCallback);

   screen_start.CreateScreen(Display_GetInputDevice());
   screen_start.RegisterButtonPressedCallback(StartScreenCallback);

   screen_setDateInitial.CreateScreen(Display_GetInputDevice(), true, false);
   screen_setDateInitial.RegisterButtonPressedCallback(SetDateButtonCallback);
   screen_setDateInitial.SetDate(1, 1, 21);

   screen_setDate.CreateScreen(Display_GetInputDevice(), true, true);
   screen_setDate.RegisterButtonPressedCallback(SetDateButtonCallback);
   screen_setDate.SetDate(1, 1, 21);

   screen_setTime.CreateScreen(Display_GetInputDevice(), true, true);
   screen_setTime.RegisterButtonPressedCallback(SetTimeButtonCallback);
   screen_setTime.SetTime(1, 1, 20);

   screen_timerRecharge.CreateScreen(Display_GetInputDevice());
   screen_timerRecharge.RegisterButtonPressedCallback(TimerRechargeScreenCallback);

   ds3231_cntl_stat_t rtcStatus;
   rtc.get_cntl_stat_reg(&rtcStatus);
   printf("RTC control: %d\r\n", rtcStatus.control);
   printf("RTC status: %d\r\n", rtcStatus.status);
   if (rtcStatus.status & OSF)
   {
      puts("RTC oscillator stopped, need to get the time from the user");
      InitRtc();
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
