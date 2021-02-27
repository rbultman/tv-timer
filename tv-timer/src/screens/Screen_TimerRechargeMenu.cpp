/*
    Screen_TimerRechargeMenu.h

    Author: Rob Bultman
    License: MIT
*/

#include <stdio.h>
#include "Screen_TimerRechargeMenu.h"

void Screen_TimerRechargeMenu::ButtonEventHandler(lv_obj_t *obj, lv_event_t event)
{
    Screen_TimerRechargeMenu *pScreen = (Screen_TimerRechargeMenu *)lv_obj_get_user_data(obj);
    lv_obj_t *label = pScreen->startTimerButtonLabel;

    switch (event)
    {
    case LV_EVENT_FOCUSED:
        Serial.println("Start timer button received focus.");
        lv_obj_set_style_local_text_color(label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
        break;
    case LV_EVENT_DEFOCUSED:
        Serial.println("Start timer button lost focus.");
        lv_obj_set_style_local_text_color(label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
        break;
    case LV_EVENT_SHORT_CLICKED:
        Serial.println("Start timer button clicked.");
        if (pScreen->buttonPressedCallback)
        {
            pScreen->buttonPressedCallback(Screen_Menu1Pressed);
        }
        break;
    }
}

lv_obj_t *Screen_TimerRechargeMenu::CreateScreen(lv_indev_t *pInputDevice, bool hasNextButton, bool hasPreviousButton)
{
    this->ScreenClass::CreateScreen(pInputDevice, hasNextButton, hasPreviousButton);

    startTimerButton = lv_btn_create(scr, NULL);
    lv_obj_set_pos(startTimerButton, 0, 0);
    lv_obj_add_style(startTimerButton, LV_BTN_PART_MAIN, &menuButtonStyle);
    lv_obj_set_width(startTimerButton, LV_HOR_RES);
    lv_obj_set_event_cb(startTimerButton, ButtonEventHandler);
    lv_obj_set_user_data(startTimerButton, this);

    startTimerButtonLabel = lv_label_create(startTimerButton, NULL);
    lv_label_set_text(startTimerButtonLabel, "Start Timer");

    group = lv_group_create();
    lv_group_add_obj(group, startTimerButton);
    if (hasNextButton)
        lv_group_add_obj(group, nextButton);
    if (hasPreviousButton)
        lv_group_add_obj(group, previousButton);

    return scr;
}

void Screen_TimerRechargeMenu::UpdateScreen(DateTime &currentTime, DateTime &alarmTime)
{
    char timeString[128];

    GetTimeRemainingString(timeString, currentTime, alarmTime);
    if (strcmp(timeString, "0") == 0)
    {
        if (buttonPressedCallback)
        {
            buttonPressedCallback(Screen_TimeoutComplete);
        }
    }
}
