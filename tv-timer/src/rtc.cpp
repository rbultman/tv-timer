/*
    rtc.cpp

    An interface file to the RTC module.

    Author: Rob Bultman
    License: MIT
*/

#include <stdio.h>
#include "rtc.h"
#include "io_ports.h"

RTC_DS3231 rtc;

void InitRtc()
{
    rtc.begin();
}

void UpdateRtc(uint8_t hours,
               uint8_t minutes,
               uint8_t seconds,
               uint8_t amPm,
               uint8_t month,
               uint8_t day,
               uint8_t year)
{
    DateTime dt(year, month, day, hours, minutes, seconds);

    rtc.adjust(dt);
}

// Assumption: The alarm will always be in the future.
#ifdef KILL
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

time_t GetAlarmEpoch(bool whichAlarm)
{
    ds3231_alrm_t alarm;
    struct tm alarmTs;
    
    // get current alarm epoch
    rtc.get_alarm(&alarm, whichAlarm);
    AlarmToTimeStruct(alarmTs, alarm);
    return mktime(&alarmTs);
}
#endif