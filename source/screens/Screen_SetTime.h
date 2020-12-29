/*
    Screen_SetTime.h

    A screen to set the date.

    Author: Rob Bultman
    License: MIT
*/

#ifndef SCREEN_SET_TIME_H
#define SCREEN_SET_TIME_H

#include "lvgl.h"
#include "screen_class.h"

class Screen_SetTime : public ScreenClass
{
public:
    lv_obj_t *CreateScreen(lv_indev_t *pInputDevice);

private:
    static void SpinboxEventHandler(lv_obj_t *obj, lv_event_t event);
    static void AmPmRollerEventHandler(lv_obj_t *obj, lv_event_t event);
    static void AcceptButtonEventHandler(lv_obj_t *obj, lv_event_t event);
    static void PreviousButtonEventHandler(lv_obj_t *obj, lv_event_t event);
    lv_obj_t *hourSpinbox;
    lv_obj_t *minuteSpinbox;
    lv_obj_t *amPmRoller;
    lv_obj_t *acceptButton;
    lv_obj_t *acceptLabel;
    lv_obj_t *previousButton;
    lv_obj_t *previousLabel;
    lv_group_t *group;
    lv_style_t style;
};

#endif // SCREEN_SET_TIME_H
