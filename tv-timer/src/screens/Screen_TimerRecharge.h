/*
    Screen_TimerRecharge.h

    A screen that shows the time, date, and a recharge counter.

    Author: Rob Bultman
    License: MIT
*/

#ifndef SCREEN_TIMER_RECHARGE_H
#define SCREEN_TIMER_RECHARGE_H

#include "lvgl.h"
#include "screen_class.h"
#include "RTClib.h"

class Screen_TimerRecharge : public ScreenClass
{
public:
    Screen_TimerRecharge() : timeLabel(NULL), dateLabel(NULL) {}
    lv_obj_t *CreateScreen(lv_indev_t *pInputDevice, bool hasNextButton = false, bool hasPreviousButton = false);
    void UpdateScreen(DateTime &currentTime, DateTime &alarmTime);

private:
    static void EventHandler(lv_obj_t *obj, lv_event_t event);
    lv_obj_t *timeLabel;
    lv_obj_t *dateLabel;
    lv_obj_t *rechargeLabel;
};

#endif // SCREEN_TIMER_RECHARGE_H
