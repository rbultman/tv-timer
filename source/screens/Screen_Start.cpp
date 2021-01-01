/*
    Screen_Start.cpp

    Start the timer or go into the setup menu.

    Author: Rob Bultman
    License: MIT
*/

#include <stdio.h>
#include "Screen_Start.h"

#define VSPACING 1

void Screen_Start::ButtonEventHandler(lv_obj_t *obj, lv_event_t event)
{
    Screen_Start *pScreen = (Screen_Start *)lv_obj_get_user_data(obj);
    lv_obj_t *label;
    uint8_t buttonPressed;

    if (obj == pScreen->startButton)
    {
        label = pScreen->startButtonLabel;
        buttonPressed = Screen_Menu1Pressed;
    }
    else if (obj == pScreen->settingsButton)
    {
        label = pScreen->settingsButtonLabel;
        buttonPressed = Screen_Menu2Pressed;
    }
    else
    {
        puts("ERROR: unknown button object.");
        return;
    }
    

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
            pScreen->buttonPressedCallback(buttonPressed);
        }
        break;
    }
}

lv_obj_t *Screen_Start::CreateScreen(lv_indev_t *pInputDevice, bool hasNextButton, bool hasPreviousButton)
{
    this->ScreenClass::CreateScreen(pInputDevice, hasNextButton, hasPreviousButton);

    startButton = lv_btn_create(scr, NULL);
    lv_obj_set_pos(startButton, 0, 0);
    lv_obj_add_style(startButton, LV_BTN_PART_MAIN, &menuButtonStyle);
    lv_obj_set_width(startButton, LV_HOR_RES);
    lv_obj_set_event_cb(startButton, ButtonEventHandler);
    lv_obj_set_user_data(startButton, this);

    startButtonLabel = lv_label_create(startButton, NULL);
    lv_label_set_text(startButtonLabel, "Start Timer");

    settingsButton = lv_btn_create(scr, NULL);
    lv_obj_add_style(settingsButton, LV_BTN_PART_MAIN, &menuButtonStyle);
    lv_obj_set_width(settingsButton, LV_HOR_RES);
    lv_obj_set_event_cb(settingsButton, ButtonEventHandler);
    lv_obj_align(settingsButton, startButton, LV_ALIGN_OUT_BOTTOM_LEFT, 0, VSPACING);
    lv_obj_set_user_data(settingsButton, this);

    settingsButtonLabel = lv_label_create(settingsButton, NULL);
    lv_label_set_text(settingsButtonLabel, "Settings");

    group = lv_group_create();
    lv_group_add_obj(group, startButton);
    lv_group_add_obj(group, settingsButton);
    if (hasNextButton)
        lv_group_add_obj(group, nextButton);
    if (hasPreviousButton)
        lv_group_add_obj(group, previousButton);

    return scr;
}
