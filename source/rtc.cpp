/*
    rtc.cpp

    An interface file to the RTC module.

    Author: Rob Bultman
    License: MIT
*/

#include <stdio.h>
#include "rtc.h"
#include "io_ports.h"

Ds3231 rtc(RTC_SDA, RTC_SCL);

 void InitRtc()
{
    ds3231_cntl_stat_t rtc_control_status = {0, 0x08};

    rtc.set_cntl_stat_reg(rtc_control_status);
}

void UpdateRtc(uint8_t hours,
               uint8_t minutes,
               uint8_t seconds,
               uint8_t amPm,
               uint8_t month,
               uint8_t day,
               uint8_t year)
{
    ds3231_time_t rtc_time;
    ds3231_calendar_t rtc_calendar;
    struct tm time;
    struct tm *pTimeConverted;
    time_t rawTime;

    rtc_calendar.date = day;
    rtc_calendar.month = month + 1;
    rtc_calendar.year = year;
    rtc_time.hours = hours;
    rtc_time.minutes = minutes;
    rtc_time.seconds = 0;
    rtc_time.am_pm = amPm;
    rtc_calendar.day = 6;
    rtc_time.mode = 1; // 12 hour mode

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

// Assumption: The alarm will always be in the future.
void AlarmToTimeStruct(struct tm &ts, ds3231_alrm_t &alarm)
{
    time_t timeEpoch;

    timeEpoch = rtc.get_epoch();
    ts = *localtime(&timeEpoch);

    // check for month rollover
    if (alarm.date < (uint32_t)ts.tm_mday)
    {
        ts.tm_mon++;
        // check for year rollover
        if (ts.tm_mon >= 12)
        {
            ts.tm_mon = 0;
            ts.tm_year++;
        }
    }
    ts.tm_hour = alarm.hours;
    ts.tm_min = alarm.minutes;
    ts.tm_sec = alarm.seconds;
    ts.tm_mday = alarm.date;
}

void InitializeAlarm(ds3231_alrm_t &alarm, struct tm &ts)
{
    alarm.date = ts.tm_mday;
    alarm.hours = ts.tm_hour;
    alarm.minutes = ts.tm_min;
    alarm.seconds = ts.tm_sec;
    alarm.dy_dt = 0;
    alarm.am1 = alarm.am2 = alarm.am3 = alarm.am4 = 0;
    alarm.mode = 0;
    alarm.day = ts.tm_wday + 1;
}

void EnableRtcInterrupt(bool alarm)
{
    ds3231_cntl_stat_t rtcReg;

    rtc.get_cntl_stat_reg(&rtcReg);

    if (alarm == ALARM1)
    {
        rtcReg.control |= A1IE;
    }
    else
    {
        rtcReg.control |= A2IE;
    }
    rtc.set_cntl_stat_reg(rtcReg);
}

void DisableRtcInterrupt(bool alarm)
{
    ds3231_cntl_stat_t rtcReg;

    rtc.get_cntl_stat_reg(&rtcReg);

    if (alarm == ALARM1)
    {
        rtcReg.control &= ~A1IE;
    }
    else
    {
        rtcReg.control &= ~A2IE;
    }
    rtc.set_cntl_stat_reg(rtcReg);
}

void ClearRtcFlag(bool alarm)
{
    ds3231_cntl_stat_t rtcReg;

    rtc.get_cntl_stat_reg(&rtcReg);

    if (alarm == ALARM1)
    {
        rtcReg.status &= A1F;
    }
    else
    {
        rtcReg.status &= A2F;
    }
    rtc.set_cntl_stat_reg(rtcReg);
}

void ClearRtcFlags()
{
    ClearRtcFlag(ALARM1);
    ClearRtcFlag(ALARM2);
}
