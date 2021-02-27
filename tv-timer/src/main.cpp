#include <lvgl.h>
#include <SPI.h>
#include <TeensyThreads.h>
#include "io_ports.h"
#include "RTClib.h"
#include "rtc.h"
#include "display.h"
#include "Screen_Time.h"
#include "Screen_SetDate.h"
#include "Screen_SetTime.h"
#include "Screen_Start.h"
#include "Screen_Timer.h"
#include "Screen_TimerMenu.h"
#include "Screen_TimerRecharge.h"
#include "Screen_TimerRechargeMenu.h"
#include "backlight.h"

static volatile uint32_t seconds = 0;
static bool timeIsInitialized = false;

#define WATCH_TIME 4500

static Screen_Time screen_time;
static Screen_SetDate screen_setDate;
static Screen_SetDate screen_setDateInitial;
static Screen_SetTime screen_setTime;
static Screen_Start screen_start;
static Screen_Timer screen_timer;
static Screen_TimerMenu screen_timerMenu;
static Screen_TimerRecharge screen_timerRecharge;
static Screen_TimerRechargeMenu screen_timerRechargeMenu;

volatile bool printmem = false;

void PrintMemUsage()
{
  lv_mem_monitor_t mon;
  lv_mem_monitor(&mon);
  Serial.print("Mem total: ");
  Serial.println(mon.total_size);
  Serial.print("Free count: ");
  Serial.println(mon.free_cnt);
  Serial.print("Available: ");
  Serial.println(mon.free_size);
  Serial.print("Biggest: ");
  Serial.println(mon.free_biggest_size);
  Serial.print("Used count: ");
  Serial.println(mon.used_cnt);
  Serial.print("Max used: ");
  Serial.println(mon.max_used);
  Serial.print("Used percent: ");
  Serial.println(mon.used_pct);
  Serial.print("Frag percent: ");
  Serial.println(mon.frag_pct);
}

void TimeScreenCallback(uint8_t whichButton)
{
  screen_start.LoadScreen();
}

void TimerScreenCallback(uint8_t whichButton)
{
  #ifdef KILL
  switch (whichButton)
  {
  case Screen_Menu1Pressed:
    screen_timerMenu.LoadScreen();
    break;
  case Screen_TimeoutComplete:
    ClearRtcFlags();
    DisableRtcInterrupt(ALARM1);
    DisableRtcInterrupt(ALARM2);
    screen_time.LoadScreen();
    break;
  }
  #endif
}

void TimerMenuScreenCallback(uint8_t whichButton)
{
  #ifdef KILL
  ds3231_alrm_t alarm;
  struct tm alarmTs;
  time_t alarmEpoch;
  time_t timeEpoch;
  time_t timeRemaining;

  switch (whichButton)
  {
  case Screen_Menu1Pressed:
    alarmEpoch = GetAlarmEpoch(ALARM1);
    // get epoch for new alarm time
    timeEpoch = rtc.get_epoch();
    timeRemaining = WATCH_TIME - (alarmEpoch - timeEpoch);
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
    break;
  case Screen_TimeoutComplete:
    ClearRtcFlags();
    DisableRtcInterrupt(ALARM1);
    DisableRtcInterrupt(ALARM2);
    screen_timerRecharge.LoadScreen();
    break;
  }
  #endif
}

void StartScreenCallback(uint8_t whichButton)
{
  DateTime now;
  DateTime alarm;

      switch (whichButton)
  {
  case Screen_PreviousButtonPressed:
    screen_time.LoadScreen();
    break;
  case Screen_Menu1Pressed:
    now = rtc.now();
    alarm = now + TimeSpan(WATCH_TIME);
    rtc.disableAlarm(ALARM1);
    rtc.clearAlarm(ALARM1);
    rtc.setAlarm1(now, DS3231_A1_Hour);
    rtc.disableAlarm(ALARM2);
    rtc.clearAlarm(ALARM2);
    screen_timer.UpdateScreen(now, alarm);
    screen_timer.LoadScreen();
    break;
  case Screen_Menu2Pressed:
    DateTime now = rtc.now();
    screen_setDate.SetDate(now.month()-1, now.day(), now.year());
    screen_setDate.LoadScreen();
    break;
  }
}

void SetDateButtonCallback(uint8_t whichButton)
{
  if (whichButton == Screen_NextButtonPressed)
  {
    DateTime now = rtc.now();
    Serial.printf("Time: %d:%02d:%02d %s\r\n", now.hour(), now.minute(), now.second(), now.twelveHour() == 1 ? "PM" : "AM");
    screen_setTime.LoadScreen();
    screen_setTime.SetTime(now.hour(), now.minute(), now.twelveHour());
  }
  else
  {
    screen_time.LoadScreen();
  }
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

    if (amPm)
    {
      hours += 12;
    }
    month++;
    UpdateRtc(hours, minutes, month, day, (uint16_t)year+2000);
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

void TimerRechargeScreenCallback(uint8_t whichButton)
{
  #ifdef KILL
  switch (whichButton)
  {
  case Screen_TimeoutComplete:
    ClearRtcFlags();
    DisableRtcInterrupt(ALARM1);
    DisableRtcInterrupt(ALARM2);
    screen_time.LoadScreen();
    break;
  case Screen_Menu1Pressed:
    screen_timerRechargeMenu.LoadScreen();
    break;
  }
  #endif
}

void TimerRechargeMenuScreenCallback(uint8_t whichButton)
{
  #ifdef KILL
  ds3231_alrm_t alarm;
  struct tm alarmTs;
  time_t alarmEpoch;
  time_t timeEpoch;
  time_t timeRemaining;

  switch (whichButton)
  {
  case Screen_Menu1Pressed:
    alarmEpoch = GetAlarmEpoch(ALARM2);
    // get epoch for new alarm time
    timeEpoch = rtc.get_epoch();
    timeRemaining = WATCH_TIME - (alarmEpoch - timeEpoch);
    alarmEpoch = timeEpoch + timeRemaining;
    alarmTs = *localtime(&alarmEpoch);
    InitializeAlarm(alarm, alarmTs);
    rtc.set_alarm(alarm, ALARM1);
    EnableRtcInterrupt(ALARM1);
    DisableRtcInterrupt(ALARM2);
    ClearRtcFlags();
    screen_timer.UpdateScreen(rtc.get_epoch(), alarm);
    screen_timer.LoadScreen();
    break;
  case Screen_PreviousButtonPressed:
    screen_timerRecharge.LoadScreen();
    break;
  case Screen_TimeoutComplete:
    ClearRtcFlags();
    DisableRtcInterrupt(ALARM1);
    DisableRtcInterrupt(ALARM2);
    screen_time.LoadScreen();
    break;
  }
  #endif
}

static void Heartbeat()
{
  DateTime alarm;
  DateTime now;

  if (lv_scr_act() == screen_time.scr)
  {
    DateTime now = rtc.now();
    screen_time.UpdateScreen(now, alarm);
  }
  else if (lv_scr_act() == screen_timer.scr)
  {
    now = rtc.now();
    alarm = rtc.getAlarm1();
    screen_timer.UpdateScreen(now, alarm);
  }
#ifdef KILL
  else if (lv_scr_act() == screen_timerMenu.scr)
  {
    rtc.get_alarm(&alarm, ALARM1);
    screen_timerMenu.UpdateScreen(rtc.get_epoch(), alarm);
  }
  else if (lv_scr_act() == screen_timerRecharge.scr)
  {
    rtc.get_alarm(&alarm, ALARM2);
    screen_timerRecharge.UpdateScreen(rtc.get_epoch(), alarm);
  }
  else if (lv_scr_act() == screen_timerRechargeMenu.scr)
  {
    rtc.get_alarm(&alarm, ALARM2);
    screen_timerRechargeMenu.UpdateScreen(rtc.get_epoch(), alarm);
  }
#endif
}

static void HeartbeatTask(int unused)
{
  while (true)
  {
    threads.delay(1500);
    Heartbeat();
    if(printmem)
    {
      PrintMemUsage();
      printmem = false;
    }
  }
}

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void PrintTime()
{
  DateTime now = rtc.now();

  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();

  Serial.print(" since midnight 1/1/1970 = ");
  Serial.print(now.unixtime());
  Serial.print("s = ");
  Serial.print(now.unixtime() / 86400L);
  Serial.println("d");
}

void testThread(int ignore)
{
  InitRtc();
  if (rtc.lostPower())
  {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  while (1)
  {
    threads.delay(5000);
    PrintTime();
  }
}

//typedef void (*lv_log_print_g_cb_t)(lv_log_level_t level, const char *, uint32_t, const char *, const char *);
void my_print(lv_log_level_t level, const char *file, uint32_t line, const char *func, const char * descr)
{

  Serial.print(file);
  Serial.print("@");
  Serial.print(line);
  Serial.print(": ");
  Serial.print(func);
  Serial.print(" - ");
  Serial.println(descr);
}

void setup()
{
  // put your setup code here, to run once:

  Serial.begin(115200);

  Serial.println("Delay...");
  delay(10000);
  Serial.println("Starting...");

  //threads.addThread(testThread, 0, 2048);

  SPI.begin();

  pinMode(LCD_DC, OUTPUT);
  pinMode(LCD_RESET, OUTPUT);
  pinMode(LCD_BACKLIGHT_RED, OUTPUT);
  pinMode(LCD_BACKLIGHT_GREEN, OUTPUT);
  pinMode(LCD_BACKLIGHT_BLUE, OUTPUT);
  pinMode(ENCODER_BUTTON, INPUT);

  Serial.println("initializing display");
  Display_Initialize();

  Serial.println("Registering print routine.");
  lv_log_register_print_cb(my_print); /* register print function for debugging */

  //  BacklighOn();

  Serial.println("Creating time screen.");
  screen_time.CreateScreen(Display_GetInputDevice(), false, false);
  screen_time.RegisterButtonPressedCallback(TimeScreenCallback);

  screen_start.CreateScreen(Display_GetInputDevice());
  screen_start.RegisterButtonPressedCallback(StartScreenCallback);

  screen_timer.CreateScreen(Display_GetInputDevice(), false, false);
  // screen_timer.RegisterButtonPressedCallback(TimerScreenCallback);

  screen_timerMenu.CreateScreen(Display_GetInputDevice());
  // screen_timerMenu.RegisterButtonPressedCallback(TimerMenuScreenCallback);

  screen_setDateInitial.CreateScreen(Display_GetInputDevice(), true, false);
  screen_setDateInitial.RegisterButtonPressedCallback(SetDateButtonCallback);
  //screen_setDateInitial.SetDate(1, 1, 21);

  screen_setDate.CreateScreen(Display_GetInputDevice(), true, true);
  screen_setDate.RegisterButtonPressedCallback(SetDateButtonCallback);
  // screen_setDate.SetDate(1, 1, 21);

  screen_setTime.CreateScreen(Display_GetInputDevice(), true, true);
  screen_setTime.RegisterButtonPressedCallback(SetTimeButtonCallback);
  // screen_setTime.SetTime(1, 1, 20);

  screen_timerRecharge.CreateScreen(Display_GetInputDevice());
  // screen_timerRecharge.RegisterButtonPressedCallback(TimerRechargeScreenCallback);

  screen_timerRechargeMenu.CreateScreen(Display_GetInputDevice());
  // screen_timerRechargeMenu.RegisterButtonPressedCallback(TimerRechargeMenuScreenCallback);

  Serial.println("Initializing RTC");
  InitRtc();
  if (rtc.lostPower())
  {
    Serial.println("RTC oscillator stopped, need to get the time from the user");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    screen_setDateInitial.LoadScreen();
  }
  else
  {
    Serial.println("RTC oscillator already configured.");
    timeIsInitialized = true;
    if (rtc.alarmEnabled(1))
    {
      Serial.println("Timer was running, loading timer screen.");
      screen_timer.LoadScreen();
    }
    else if (rtc.alarmEnabled(2))
    {
      Serial.println("Timer was recharging, loading recharge screen.");
      screen_timerRecharge.LoadScreen();
    }
    else
    {
      screen_time.LoadScreen();
    }
  }

  Serial.print("Starting HeartbeatTask on ID ");
  Serial.println(threads.addThread(HeartbeatTask, 1, 4096));

  Serial.println("Setup complete.");
}

void loop() {
  // put your main code here, to run repeatedly:
  Display_Loop();
}
