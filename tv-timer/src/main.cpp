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

static const char dateTimeStringFormat[] = "MM/DD/YYYY hh:mm:ss AP";

// #define WATCH_TIME 4500
// #define RECHARGE_TIME 7200
#define WATCH_TIME 60
#define RECHARGE_TIME 120

static Screen_Time screen_time;
static Screen_SetDate screen_setDate;
static Screen_SetDate screen_setDateInitial;
static Screen_SetTime screen_setTime;
static Screen_Start screen_start;
static Screen_Timer screen_timer;
static Screen_TimerMenu screen_timerMenu;
static Screen_TimerRecharge screen_timerRecharge;

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
  DateTime now = rtc.now();
  DateTime alarmTime;
  TimeSpan rechargeTime(RECHARGE_TIME);
  char buf[sizeof(dateTimeStringFormat)];

  switch (whichButton)

  {
  case Screen_Menu1Pressed:
    screen_timerMenu.LoadScreen();
    break;
  case Screen_TimeoutComplete:
    Serial.println("Timeout, watch time is over, transitioning to recharge screen.");
    rtc.disableAlarm(ALARM1);
    rtc.disableAlarm(ALARM2);
    rtc.clearAlarm(ALARM1);
    rtc.clearAlarm(ALARM2);
    Serial.printf("Recharge time is %d\r\n", rechargeTime.totalseconds());
    alarmTime = now + rechargeTime;
    strcpy(buf, dateTimeStringFormat);
    now.toString(buf);
    Serial.printf("Now  : %s\r\n", buf);
    strcpy(buf, dateTimeStringFormat);
    alarmTime.toString(buf);
    Serial.printf("Alarm: %s\r\n", buf);
    rtc.setAlarm2(alarmTime, DS3231_A2_Date);
    screen_timerRecharge.LoadScreen();
    break;
  }
}

void TimerMenuScreenCallback(uint8_t whichButton)
{
  DateTime now = rtc.now();
  DateTime alarmTime;
  TimeSpan timeRemaining;
  char buf[sizeof(dateTimeStringFormat)];

  switch (whichButton)
  {
  case Screen_Menu1Pressed:
    Serial.println("User stopped watching, transitioning to recharge screen.");
    alarmTime = rtc.getAlarm1();
    rtc.disableAlarm(ALARM1);
    rtc.disableAlarm(ALARM2);
    rtc.clearAlarm(ALARM1);
    rtc.clearAlarm(ALARM2);
    alarmTime = ConvertAlarmToDate(now, alarmTime);
    timeRemaining = TimeSpan(RECHARGE_TIME) - (alarmTime - now);
    alarmTime = now + timeRemaining;
    rtc.setAlarm2(alarmTime, DS3231_A2_Date);
    screen_timerRecharge.UpdateScreen(now, alarmTime);
    screen_timerRecharge.LoadScreen();
    break;
  case Screen_PreviousButtonPressed:
    screen_timer.LoadScreen();
    break;
  case Screen_TimeoutComplete:
    Serial.println("Timeout, watch time is over, transitioning to recharge screen.");
    rtc.disableAlarm(ALARM1);
    rtc.disableAlarm(ALARM2);
    rtc.clearAlarm(ALARM1);
    rtc.clearAlarm(ALARM2);
    alarmTime = now + TimeSpan(RECHARGE_TIME);
    strcpy(buf, dateTimeStringFormat);
    now.toString(buf);
    Serial.printf("Now  : %s\r\n", buf);
    strcpy(buf, dateTimeStringFormat);
    alarmTime.toString(buf);
    Serial.printf("Alarm: %s\r\n", buf);
    rtc.setAlarm2(alarmTime, DS3231_A2_Date);
    screen_timerRecharge.LoadScreen();
    break;
  }
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
    rtc.setAlarm1(alarm, DS3231_A1_Date);
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
    screen_setTime.SetTime(now);
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
  uint16_t year;

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
    UpdateRtc(hours, minutes, month, day, year);
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
  switch (whichButton)
  {
  case Screen_TimeoutComplete:
    Serial.println("Timeout, recharge complete, transitioning to time screen.");
    rtc.disableAlarm(ALARM1);
    rtc.clearAlarm(ALARM1);
    rtc.disableAlarm(ALARM2);
    rtc.clearAlarm(ALARM2);
    screen_time.LoadScreen();
    break;
  }
}

static void Heartbeat()
{
  DateTime alarm;
  DateTime now = rtc.now();

  if (lv_scr_act() == screen_time.scr)
  {
    screen_time.UpdateScreen(now, alarm);
  }
  else if (lv_scr_act() == screen_timer.scr)
  {
    alarm = rtc.getAlarm1();
    screen_timer.UpdateScreen(now, alarm);
  }
  else if (lv_scr_act() == screen_timerMenu.scr)
  {
    alarm = rtc.getAlarm1();
    screen_timerMenu.UpdateScreen(now, alarm);
  }
  else if (lv_scr_act() == screen_timerRecharge.scr)
  {
    alarm = rtc.getAlarm2();
    screen_timerRecharge.UpdateScreen(now, alarm);
  }
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
  screen_timer.RegisterButtonPressedCallback(TimerScreenCallback);

  screen_timerMenu.CreateScreen(Display_GetInputDevice());
  screen_timerMenu.RegisterButtonPressedCallback(TimerMenuScreenCallback);

  screen_setDateInitial.CreateScreen(Display_GetInputDevice(), true, false);
  screen_setDateInitial.RegisterButtonPressedCallback(SetDateButtonCallback);

  screen_setDate.CreateScreen(Display_GetInputDevice(), true, true);
  screen_setDate.RegisterButtonPressedCallback(SetDateButtonCallback);

  screen_setTime.CreateScreen(Display_GetInputDevice(), true, true);
  screen_setTime.RegisterButtonPressedCallback(SetTimeButtonCallback);

  screen_timerRecharge.CreateScreen(Display_GetInputDevice());
  screen_timerRecharge.RegisterButtonPressedCallback(TimerRechargeScreenCallback);

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
    // if (rtc.alarmEnabled(1))
    // {
    //   Serial.println("Timer was running, loading timer screen.");
    //   screen_timer.LoadScreen();
    // }
    // else if (rtc.alarmEnabled(2))
    // {
    //   Serial.println("Timer was recharging, loading recharge screen.");
    //   screen_timerRecharge.LoadScreen();
    // }
    // else
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
