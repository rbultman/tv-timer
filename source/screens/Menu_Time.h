/*
    Menu_Time.h

    A screen that just shows the time and date.

    Author: Rob Bultman
    License: MIT
*/

#ifndef MENU_TIME_H
#define MENU_TIME_H

#include "lvgl.h"
#include "screen_class.h"

class MenuTime : public ScreenClass
{
    void Create(lv_indev_t *pInputDevice);
};

lv_obj_t *MenuTime_CreateScreen(lv_indev_t *pInputDevice);
void MenuTime_UpdateScreen(
    uint8_t hours, 
    uint8_t minutes, 
    uint8_t seconds, 
    uint8_t month, 
    uint8_t day, 
    uint8_t year);

#endif // MENU_TIME_H
