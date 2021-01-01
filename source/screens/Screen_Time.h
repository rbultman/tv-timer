/*
    Screen_Time.h

    A screen that just shows the time and date.

    Author: Rob Bultman
    License: MIT
*/

#ifndef SCREEN_TIME_H
#define SCREEN_TIME_H

#include "lvgl.h"
#include "screen_class.h"

class Screen_Time : public ScreenClass
{
    public:
        Screen_Time() : timeLabel(NULL), dateLabel(NULL) {}
        lv_obj_t *CreateScreen(lv_indev_t *pInputDevice, bool hasNextButton = false, bool hasPreviousButton = false);
        void UpdateScreen(
            uint8_t hours,
            uint8_t minutes,
            uint8_t seconds,
            uint8_t amPm,
            uint8_t month,
            uint8_t day,
            uint8_t year);

    private:
        static void EventHandler(lv_obj_t *obj, lv_event_t event);
        lv_obj_t *timeLabel;
        lv_obj_t *dateLabel;
};

#endif // SCREEN_TIME_H
