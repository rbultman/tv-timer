/*
    Menu_Time.cpp

    A screen that just shows the time and date.

    Author: Rob Bultman
    License: MIT
*/

#include "Menu_Time.h"

static lv_indev_t *pInputDevice = NULL;

lv_obj_t *MenuTime_CreateScreen(lv_indev_t *_pInputDevice)
{
    static lv_obj_t *scr = NULL;
    pInputDevice = _pInputDevice;

    if (scr)
    {
        lv_obj_del(scr);
    }
    // the main screen object
    scr = lv_obj_create(NULL, NULL);
    lv_obj_set_size(scr, LV_HOR_RES, LV_VER_RES);

    return scr;
}

void MenuTime_UpdateScreen()
{

}
