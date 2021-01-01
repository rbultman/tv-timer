/*
    Screen_Timer.h

    Shows the countdown timer.

    Author: Rob Bultman
    License: MIT
*/

#ifndef SCREEN_TIMER_H
#define SCREEN_TIMER_H

#include <ctime>
#include "lvgl.h"
#include "screen_class.h"
#include "ds3231.h"

class Screen_Timer : public ScreenClass
{
public:
    lv_obj_t *CreateScreen(lv_indev_t *pInputDevice, bool hasNextButton = false, bool hasPreviousButton = false);
    void UpdateScreen(time_t currentTime, ds3231_alrm_t &alarmTime);

private:
    static void EventHandler(lv_obj_t *obj, lv_event_t event);
    lv_obj_t *timeRemainingLabel;
};

#endif // SCREEN_TIMER_H
