/*
    rtc.h

    An interface file to the RTC module.

    Author: Rob Bultman
    License: MIT
*/

#ifndef RTC_H
#define RTC_H

#include <time.h>
#include <RTClib.h>

#define ALARM1 true
#define ALARM2 false

extern RTC_DS3231 rtc;

void InitRtc();
void UpdateRtc(uint8_t hours,
               uint8_t minutes,
               uint8_t month,
               uint8_t day,
               uint16_t year);
DateTime ConvertAlarmToDate(DateTime currentTime, DateTime alarmTime);

#endif // RTC_H
