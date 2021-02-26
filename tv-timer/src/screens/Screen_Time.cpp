/*
    Screen_Time.cpp

    A screen that just shows the time and date.

    Author: Rob Bultman
    License: MIT
*/

#include <stdio.h>
#include <stdlib.h>
#include "Screen_Time.h"

void Screen_Time::EventHandler(lv_obj_t *obj, lv_event_t event)
{
    Screen_Time *pScreen = (Screen_Time *)lv_obj_get_user_data(obj);

    switch (event)
    {
    case LV_EVENT_SHORT_CLICKED:
        if (pScreen->buttonPressedCallback)
        {
            pScreen->buttonPressedCallback(Screen_Menu1Pressed);
        }
        break;
    }
}

lv_obj_t *Screen_Time::CreateScreen(lv_indev_t *pInputDevice, bool hasNextButton, bool hasPreviousButton)
{
    this->ScreenClass::CreateScreen(pInputDevice, hasNextButton, hasPreviousButton);

    lv_obj_t *cont;

    cont = lv_cont_create(scr, NULL);
    lv_obj_set_size(cont, LV_HOR_RES, LV_VER_RES);
    lv_obj_align(cont, scr, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_auto_realign(cont, true);                   /*Auto realign when the size changes*/
    lv_obj_align_origo(cont, NULL, LV_ALIGN_CENTER, 0, 0); /*This parametrs will be sued when realigned*/
    lv_cont_set_fit(cont, LV_FIT_TIGHT);
    lv_cont_set_layout(cont, LV_LAYOUT_COLUMN_MID);
    lv_obj_set_event_cb(cont, EventHandler);
    lv_obj_set_user_data(cont, this);

    timeLabel = lv_label_create(cont, NULL); /*Create a label*/
    lv_label_set_text(timeLabel, "TIME");    /*Set the labels text*/

    dateLabel = lv_label_create(cont, timeLabel); /*Create a label*/
    lv_label_set_text(dateLabel, "DATE");         /*Set the labels text*/

    group = lv_group_create();
    lv_group_add_obj(group, cont);

    return scr;
}

void Screen_Time::UpdateScreen(DateTime &currentTime, DateTime &alarmTime)
{
    static char msg[64];

    if (scr)
    {
        if (timeLabel)
        {
            GetTimeString(msg, currentTime);
            lv_label_set_text(timeLabel, msg);
        }
        
        if (dateLabel)
        {
            GetDateString(msg, currentTime);
            lv_label_set_text(dateLabel, msg);
        }
    }
}
