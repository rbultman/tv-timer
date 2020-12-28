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
        ScreenClass() { scr  = NULL; pInputDevice = NULL;}
        void Create(lv_indev_t *pInputDevice)
        {
            this->pInputDevice = pInputDevice;

            if (scr)
            {
                lv_obj_del(scr);
            }
            // the main screen object
            scr = lv_obj_create(NULL, NULL);
            lv_obj_set_size(scr, LV_HOR_RES, LV_VER_RES);
        }

    private:
        lv_obj_t *scr;
        lv_indev_t *pInputDevice;
};

#endif // SCREEN_CLASS_H
