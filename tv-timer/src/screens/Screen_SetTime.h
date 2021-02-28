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
    lv_obj_t *CreateScreen(lv_indev_t *pInputDevice, bool hasNextButton = false, bool hasPreviousButton = false);
    void SetTime(DateTime &dt);
    void GetTime(uint8_t *hours, uint8_t *minutes, uint8_t *amPm);

private:
    static void SpinboxEventHandler(lv_obj_t *obj, lv_event_t event);
    static void AmPmRollerEventHandler(lv_obj_t *obj, lv_event_t event);
    static void AcceptButtonEventHandler(lv_obj_t *obj, lv_event_t event);
    static void PreviousButtonEventHandler(lv_obj_t *obj, lv_event_t event);
    lv_obj_t *hourSpinbox;
    lv_obj_t *minuteSpinbox;
    lv_obj_t *amPmRoller;
    uint8_t hours;
    uint8_t minutes;
    uint8_t amPm;
};

#endif // SCREEN_SET_TIME_H
