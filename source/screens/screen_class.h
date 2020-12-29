/*
    screen_class.h

    A utility class for screens.

    Author: Rob Bultman
    License: MIT
*/

#ifndef SCREEN_CLASS_H
#define SCREEN_CLASS_H

#include "lvgl.h"

class ScreenClass 
{
    public:
        ScreenClass();
        lv_obj_t * CreateScreen(lv_indev_t *pInputDevice);

    protected:
        void InitializeStyles();
        lv_obj_t *scr;
        lv_indev_t *pInputDevice;
        static lv_style_t menuButtonStyle;
        static lv_style_t dialogButtonStyle;
        static lv_style_t spinboxStyle;
        static bool stylesInitialized;
};

#endif // SCREEN_CLASS_H
