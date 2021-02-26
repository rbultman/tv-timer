/*
    Screen_TimerRechargeMenu.h

    Author: Rob Bultman
    License: MIT
*/

#ifndef SCREEN_TIMER_RECHARGE_MENU_H
#define SCREEN_TIMER_RECHARGE_MENU_H

#include "lvgl.h"
#include "screen_class.h"

class Screen_TimerRechargeMenu : public ScreenClass
{
public:
    lv_obj_t *CreateScreen(lv_indev_t *pInputDevice, bool hasNextButton = false, bool hasPreviousButton = true);
    void UpdateScreen(DateTime &currentTime, DateTime &alarmTime);

private:
    static void ButtonEventHandler(lv_obj_t *obj, lv_event_t event);
    lv_obj_t *startTimerButton;
    lv_obj_t *startTimerButtonLabel;
};

#endif // SCREEN_TIMER_RECHARGE_MENU_H
