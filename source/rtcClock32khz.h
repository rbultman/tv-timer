/*
    rtcClock32khz.h

    Stuff related to reading the 32Khz input from the RTC.

    Initializes the peripheral and timer to accept input from the
    32Khz output from the RTC and call a callback once per second.
    
    Author: Rob Bultman
    License: MIT
*/

#ifndef RTC_CLOCK_32_KHZ_H
#define RTC_CLOCK_32_KHZ_H

#include "system_RZ_A1H.h"
#include "mbed.h"

void InitRtcClock32khzInput(IRQHandler isrHandler);

#endif // RTC_CLOCK_32_KHZ_H
