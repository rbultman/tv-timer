/*
    Screen_Start.h

    Start the timer or go into the setup menu.

    Author: Rob Bultman
    License: MIT
*/

#ifndef SCREEN_START_H
#define SCREEN_START_H

#include "lvgl.h"
#include "screen_class.h"

class Screen_Start : public ScreenClass
{
public:
    lv_obj_t *CreateScreen(lv_indev_t *pInputDevice, bool hasNextButton = false, bool hasPreviousButton = true);

private:
    static void ButtonEventHandler(lv_obj_t *obj, lv_event_t event);
    lv_obj_t *startButton;
    lv_obj_t *startButtonLabel;
    lv_obj_t *settingsButton;
    lv_obj_t *settingsButtonLabel;
};

#endif // SCREEN_START_H
