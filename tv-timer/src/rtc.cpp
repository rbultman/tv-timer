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
               uint8_t month,
               uint8_t day,
               uint16_t year)
{
    DateTime dt(year, month, day, hours, minutes, 0);

    Serial.printf("Setting date to %d/%d/%d %d:%02d\r\n", month, day, year, hours, minutes);
    Serial.printf("Setting date to %d/%d/%d %d:%02d\r\n", dt.month(), dt.day(), dt.year(), dt.hour(), dt.minute());

    rtc.adjust(dt);
}

DateTime ConvertAlarmToDate(DateTime currentTime, DateTime alarmTime)
{
    uint8_t alarmMonth = currentTime.month();
    uint16_t alarmYear = currentTime.year();
    DateTime alarmDateTime;
    TimeSpan timeRemaining;

    if (alarmTime.day() < (uint32_t)currentTime.day())
    {
        alarmMonth++;
        if (alarmMonth > 12)
        {
            alarmYear++;
            alarmMonth = 1;
        }
    }

    return DateTime(alarmYear, alarmMonth, alarmTime.day(), alarmTime.hour(), alarmTime.minute(), alarmTime.second());
}
