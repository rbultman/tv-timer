/*
    Screen_SetDate.h

    A screen to set the date.

    Author: Rob Bultman
    License: MIT
*/

#ifndef SCREEN_SET_DATE_H
#define SCREEN_SET_DATE_H

#include "lvgl.h"
#include "screen_class.h"

class Screen_SetDate : public ScreenClass
{
public:
    lv_obj_t *CreateScreen(lv_indev_t *pInputDevice, bool hasNextButton = false, bool hasPreviousButton = false);
    void SetDate(uint8_t month, uint8_t day, uint16_t year);
    void GetDate(uint8_t *month, uint8_t *day, uint16_t *year);

private:
    static void SpinboxEventHandler(lv_obj_t *obj, lv_event_t event);
    static void RollerEventHandler(lv_obj_t *obj, lv_event_t event);
    lv_obj_t *monthRoller;
    lv_obj_t *daySpinbox;
    lv_obj_t *yearSpinbox;
    uint8_t month;
    uint8_t day;
    uint16_t year;
};

#endif // SCREEN_SET_DATE_H
