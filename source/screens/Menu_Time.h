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

class Menu_Time : public ScreenClass
{
    public:
        Menu_Time() : timeLabel(NULL), dateLabel(NULL) {}
        lv_obj_t *CreateScreen(lv_indev_t *pInputDevice);
        void UpdateScreen(
            uint8_t hours,
            uint8_t minutes,
            uint8_t seconds,
            uint8_t month,
            uint8_t day,
            uint8_t year);

    private:
        lv_obj_t *timeLabel;
        lv_obj_t *dateLabel;
};

#endif // MENU_TIME_H
