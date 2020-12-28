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
    lv_obj_t *CreateScreen(lv_indev_t *pInputDevice);

private:
};

#endif // SCREEN_SET_DATE_H
