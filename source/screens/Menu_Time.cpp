/*
    Menu_Time.cpp

    A screen that just shows the time and date.

    Author: Rob Bultman
    License: MIT
*/

#include <stdio.h>
#include <stdlib.h>
#include "Menu_Time.h"

static lv_obj_t *scr = NULL;
static lv_indev_t *pInputDevice = NULL;
static lv_obj_t *timeLabel;
static lv_obj_t *dateLabel;

lv_obj_t *MenuTime_CreateScreen(lv_indev_t *_pInputDevice)
{
    pInputDevice = _pInputDevice;

    if (scr)
    {
        lv_obj_del(scr);
    }
    // the main screen object
    scr = lv_obj_create(NULL, NULL);
    lv_obj_set_size(scr, LV_HOR_RES, LV_VER_RES);

    lv_obj_t *cont;

    cont = lv_cont_create(scr, NULL);
    lv_obj_set_size(cont, LV_HOR_RES, LV_VER_RES);
    lv_obj_align(cont, scr, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_auto_realign(cont, true);                   /*Auto realign when the size changes*/
    lv_obj_align_origo(cont, NULL, LV_ALIGN_CENTER, 0, 0); /*This parametrs will be sued when realigned*/
    lv_cont_set_fit(cont, LV_FIT_TIGHT);
    lv_cont_set_layout(cont, LV_LAYOUT_COLUMN_MID);

    timeLabel = lv_label_create(cont, NULL); /*Create a label*/
    lv_label_set_text(timeLabel, "TIME"); /*Set the labels text*/

    dateLabel = lv_label_create(cont, timeLabel);      /*Create a label*/
    lv_label_set_text(dateLabel, "DATE");              /*Set the labels text*/

    return scr;
}

void MenuTime_UpdateScreen(uint8_t hours, uint8_t minutes, uint8_t seconds, uint8_t month, uint8_t day, uint8_t year)
{
    char msg[64];

    if (scr)
    {
        sprintf(msg, "%d:%02d:%02d", hours, minutes, seconds);
        lv_label_set_text(timeLabel, msg);

        sprintf(msg, "%d/%d/%d", month, day, year+2000);
        lv_label_set_text(dateLabel, msg);
    }
}
