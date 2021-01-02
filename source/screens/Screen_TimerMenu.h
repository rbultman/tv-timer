/*
    Screen_TimerMenu.h

    Author: Rob Bultman
    License: MIT
*/

#ifndef SCREEN_TIMER_MENU_H
#define SCREEN_TIMER_MENU_H

#include "lvgl.h"
#include "screen_class.h"

class Screen_TimerMenu : public ScreenClass
{
public:
    lv_obj_t *CreateScreen(lv_indev_t *pInputDevice, bool hasNextButton = false, bool hasPreviousButton = true);

private:
    static void ButtonEventHandler(lv_obj_t *obj, lv_event_t event);
    lv_obj_t *stopTimerButton;
    lv_obj_t *stopTimerButtonLabel;
};

#endif // SCREEN_TIMER_MENU_H
