/*
    rtc.h

    An interface file to the RTC module.

    Author: Rob Bultman
    License: MIT
*/

#ifndef RTC_H
#define RTC_H

#include "mbed.h"
#include "ds3231/ds3231.h"

#define ALARM1 true
#define ALARM2 false

extern Ds3231 rtc;

void InitRtc();
void UpdateRtc(uint8_t hours,
               uint8_t minutes,
               uint8_t seconds,
               uint8_t amPm,
               uint8_t month,
               uint8_t day,
               uint8_t year);
void AlarmToTimeStruct(struct tm & ts, ds3231_alrm_t & alarm);
void InitializeAlarm(ds3231_alrm_t &alarm, struct tm &ts);
void EnableRtcInterrupt(bool alarm);
void DisableRtcInterrupt(bool alarm);
void ClearRtcFlag(bool alarm);
void ClearRtcFlags();
time_t GetAlarmEpoch(bool whichAlarm);

#endif // RTC_H
