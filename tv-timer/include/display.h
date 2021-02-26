/*
    display.h

    A wrapper and interface file for the display and encoder

    Author: Rob Bultman
    License: MIT
*/

#ifndef DISPLAY_H
#define DISPLAY_H

#include "lvgl.h"

void Display_Initialize(void);
void Display_Loop();
lv_indev_t *Display_GetInputDevice();

#endif // DISPLAY_H
