/*
    Screen_TimerMenu.h

    Author: Rob Bultman
    License: MIT
*/

#include <stdio.h>
#include "Screen_TimerMenu.h"

#define VSPACING 1

void Screen_TimerMenu::ButtonEventHandler(lv_obj_t *obj, lv_event_t event)
{
    Screen_TimerMenu *pScreen = (Screen_TimerMenu *)lv_obj_get_user_data(obj);
    lv_obj_t *label = pScreen->stopTimerButtonLabel;

    switch (event)
    {
    case LV_EVENT_FOCUSED:
        lv_obj_set_style_local_text_color(label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
        break;
    case LV_EVENT_DEFOCUSED:
        lv_obj_set_style_local_text_color(label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
        break;
    case LV_EVENT_SHORT_CLICKED:
        if (pScreen->buttonPressedCallback)
        {
            pScreen->buttonPressedCallback(Screen_Menu1Pressed);
        }
        break;
    }
}

lv_obj_t *Screen_TimerMenu::CreateScreen(lv_indev_t *pInputDevice, bool hasNextButton, bool hasPreviousButton)
{
    this->ScreenClass::CreateScreen(pInputDevice, hasNextButton, hasPreviousButton);

    stopTimerButton = lv_btn_create(scr, NULL);
    lv_obj_set_pos(stopTimerButton, 0, 0);
    lv_obj_add_style(stopTimerButton, LV_BTN_PART_MAIN, &menuButtonStyle);
    lv_obj_set_width(stopTimerButton, LV_HOR_RES);
    lv_obj_set_event_cb(stopTimerButton, ButtonEventHandler);
    lv_obj_set_user_data(stopTimerButton, this);

    stopTimerButtonLabel = lv_label_create(stopTimerButton, NULL);
    lv_label_set_text(stopTimerButtonLabel, "Stop Timer");

    group = lv_group_create();
    lv_group_add_obj(group, stopTimerButton);
    if (hasNextButton)
        lv_group_add_obj(group, nextButton);
    if (hasPreviousButton)
        lv_group_add_obj(group, previousButton);

    return scr;
}

void Screen_TimerMenu::UpdateScreen(DateTime &currentTime, DateTime &alarmTime)
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
