/*
    Screen_Timer.cpp

    Shows the countdown timer.

    Author: Rob Bultman
    License: MIT
*/

#include "Screen_Timer.h"

void Screen_Timer::EventHandler(lv_obj_t *obj, lv_event_t event)
{
    Screen_Timer *pScreen = (Screen_Timer *)lv_obj_get_user_data(obj);

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

lv_obj_t *Screen_Timer::CreateScreen(lv_indev_t *pInputDevice, bool hasNextButton, bool hasPreviousButton)
{
    this->ScreenClass::CreateScreen(pInputDevice, hasNextButton, hasPreviousButton);

    lv_obj_t *cont;

    cont = lv_cont_create(scr, NULL);
    lv_obj_set_size(cont, LV_HOR_RES, LV_VER_RES);
    lv_obj_align(cont, scr, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_auto_realign(cont, true);                   
    lv_obj_align_origo(cont, NULL, LV_ALIGN_CENTER, 0, 0); 
    lv_cont_set_fit(cont, LV_FIT_TIGHT);
    lv_cont_set_layout(cont, LV_LAYOUT_COLUMN_MID);
    lv_obj_set_event_cb(cont, EventHandler);
    lv_obj_set_user_data(cont, this);

    lv_obj_t * headerLabel = lv_label_create(cont, NULL); 
    lv_label_set_text(headerLabel, "Watch Time Left");    

    timeRemainingLabel = lv_label_create(cont, headerLabel); 
    lv_label_set_text(timeRemainingLabel, "");         

    group = lv_group_create();
    lv_group_add_obj(group, cont);

    return scr;
}

void Screen_Timer::UpdateScreen(DateTime &currentTime, DateTime &alarmTime)
{
    char timeString[128];

    if (!scr)
        return;

    GetTimeRemainingString(timeString, currentTime, alarmTime);
    lv_label_set_text(timeRemainingLabel, timeString);
    if (strcmp(timeString, "0") == 0)
    {
        if (buttonPressedCallback)
        {
            buttonPressedCallback(Screen_TimeoutComplete);
        }
    }
}
