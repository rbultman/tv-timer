/*
    screen_class.cpp

    A utility class for screens.

    Author: Rob Bultman
    License: MIT
*/

#include <stdio.h>
#include "screen_class.h"

lv_style_t ScreenClass::menuButtonStyle;
lv_style_t ScreenClass::dialogButtonStyle;
lv_style_t ScreenClass::spinboxStyle;
lv_style_t ScreenClass::rollerStyle;
lv_style_t ScreenClass::rollerSelectedStyle;
bool ScreenClass::stylesInitialized = false;
lv_indev_t * ScreenClass::pInputDevice = NULL;

ScreenClass::ScreenClass()
{
    scr = NULL;
    pInputDevice = NULL;
    buttonPressedCallback = NULL;
}

lv_obj_t *ScreenClass::CreateScreen(lv_indev_t *_pInputDevice, bool hasNextButton, bool hasPreviousButton)
{
    pInputDevice = _pInputDevice;
    this->hasNextButton = hasNextButton;
    this->hasPreviousButton = hasPreviousButton;

    InitializeStyles();

    if (scr)
    {
        lv_obj_del(scr);
    }
    // the main screen object
    scr = lv_obj_create(NULL, NULL);
    lv_obj_set_user_data(scr, this);

    lv_obj_set_size(scr, LV_HOR_RES, LV_VER_RES);

    if (hasNextButton)
    {
        nextButton = lv_btn_create(scr, NULL);
        lv_obj_set_event_cb(nextButton, NextButtonEventHandler);
        lv_obj_set_width(nextButton, 60);
        lv_obj_add_style(nextButton, LV_BTN_PART_MAIN, &dialogButtonStyle);
        lv_obj_set_user_data(nextButton, this);
        lv_obj_set_pos(nextButton,
                       LV_HOR_RES - lv_obj_get_width(nextButton),
                       LV_VER_RES - lv_obj_get_height(nextButton));

        nextLabel = lv_label_create(nextButton, NULL);
        lv_label_set_text(nextLabel, "Next");
    }

    if (hasPreviousButton)
    {
        previousButton = lv_btn_create(scr, NULL);
        lv_obj_set_event_cb(previousButton, PreviousButtonEventHandler);
        lv_obj_set_width(previousButton, 60);
        lv_obj_add_style(previousButton, LV_BTN_PART_MAIN, &dialogButtonStyle);
        lv_obj_set_user_data(previousButton, this);
        lv_obj_set_pos(previousButton,
                       0,
                       LV_VER_RES - lv_obj_get_height(previousButton));

        previousLabel = lv_label_create(previousButton, NULL);
        lv_label_set_text(previousLabel, "Prev");
    }

    return scr;
}

void ScreenClass::LoadScreen()
{
    Serial.println("Loading screen...");
    lv_scr_load(scr);
    Serial.println("setting input group...");
    lv_indev_set_group(pInputDevice, group);
    Serial.println("Screen load complete.");
}

void ScreenClass::InitializeStyles()
{
    if (!stylesInitialized)
    {
        // menu button default style
        lv_style_init(&menuButtonStyle);
        lv_style_set_border_width(&menuButtonStyle, LV_STATE_DEFAULT, 1);
        lv_style_set_border_color(&menuButtonStyle, LV_STATE_DEFAULT, LV_COLOR_BLACK);
        lv_style_set_bg_color(&menuButtonStyle, LV_STATE_DEFAULT, LV_COLOR_WHITE);
        lv_style_set_text_color(&menuButtonStyle, LV_STATE_DEFAULT, LV_COLOR_BLACK);
        lv_style_set_radius(&menuButtonStyle, LV_STATE_DEFAULT, 0);
        // focused style
        lv_style_set_border_width(&menuButtonStyle, LV_STATE_FOCUSED, 1);
        lv_style_set_border_color(&menuButtonStyle, LV_STATE_FOCUSED, LV_COLOR_WHITE);
        lv_style_set_bg_color(&menuButtonStyle, LV_STATE_FOCUSED, LV_COLOR_BLACK);
        lv_style_set_text_color(&menuButtonStyle, LV_STATE_FOCUSED, LV_COLOR_WHITE);
        lv_style_set_radius(&menuButtonStyle, LV_STATE_FOCUSED, 0);

        // dialog button default style
        lv_style_init(&dialogButtonStyle);
        lv_style_set_border_width(&dialogButtonStyle, LV_STATE_DEFAULT, 1);
        lv_style_set_border_color(&dialogButtonStyle, LV_STATE_DEFAULT, LV_COLOR_BLACK);
        lv_style_set_bg_color(&dialogButtonStyle, LV_STATE_DEFAULT, LV_COLOR_WHITE);
        lv_style_set_text_color(&dialogButtonStyle, LV_STATE_DEFAULT, LV_COLOR_BLACK);
        // focused style
        lv_style_set_border_width(&dialogButtonStyle, LV_STATE_FOCUSED, 1);
        lv_style_set_border_color(&dialogButtonStyle, LV_STATE_FOCUSED, LV_COLOR_WHITE);
        lv_style_set_bg_color(&dialogButtonStyle, LV_STATE_FOCUSED, LV_COLOR_BLACK);
        lv_style_set_text_color(&dialogButtonStyle, LV_STATE_FOCUSED, LV_COLOR_WHITE);

        // default style
        lv_style_init(&spinboxStyle);
        lv_style_set_border_width(&spinboxStyle, LV_STATE_DEFAULT, 1);
        lv_style_set_border_color(&spinboxStyle, LV_STATE_DEFAULT, LV_COLOR_BLACK);
        lv_style_set_bg_color(&spinboxStyle, LV_STATE_DEFAULT, LV_COLOR_WHITE);
        lv_style_set_text_color(&spinboxStyle, LV_STATE_DEFAULT, LV_COLOR_BLACK);
        lv_style_set_radius(&spinboxStyle, LV_STATE_DEFAULT, 0);
        // focused style
        lv_style_set_border_width(&spinboxStyle, LV_STATE_FOCUSED, 1);
        lv_style_set_border_color(&spinboxStyle, LV_STATE_FOCUSED, LV_COLOR_WHITE);
        lv_style_set_bg_color(&spinboxStyle, LV_STATE_FOCUSED, LV_COLOR_BLACK);
        lv_style_set_text_color(&spinboxStyle, LV_STATE_FOCUSED, LV_COLOR_WHITE);
        lv_style_set_radius(&spinboxStyle, LV_STATE_FOCUSED, 0);

        // roller style
        lv_style_init(&rollerStyle);
        lv_style_set_text_color(&rollerStyle, LV_STATE_DEFAULT, LV_COLOR_BLACK);
        lv_style_set_bg_color(&rollerStyle, LV_STATE_DEFAULT, LV_COLOR_WHITE);
        lv_style_set_text_line_space(&rollerStyle, LV_STATE_DEFAULT, 1);
        lv_style_set_text_sel_color(&rollerStyle, LV_STATE_DEFAULT, LV_COLOR_BLACK);

        lv_style_set_text_color(&rollerStyle, LV_STATE_FOCUSED, LV_COLOR_WHITE);
        lv_style_set_bg_color(&rollerStyle, LV_STATE_FOCUSED, LV_COLOR_BLACK);
        lv_style_set_text_line_space(&rollerStyle, LV_STATE_FOCUSED, 1);
        lv_style_set_text_sel_color(&rollerStyle, LV_STATE_FOCUSED, LV_COLOR_WHITE);

        lv_style_set_text_color(&rollerStyle, LV_STATE_EDITED, LV_COLOR_WHITE);
        lv_style_set_bg_color(&rollerStyle, LV_STATE_EDITED, LV_COLOR_BLACK);
        lv_style_set_text_line_space(&rollerStyle, LV_STATE_EDITED, 1);
        lv_style_set_text_sel_color(&rollerStyle, LV_STATE_EDITED, LV_COLOR_WHITE);

        // roller selected style
        lv_style_init(&rollerSelectedStyle);
        lv_style_set_border_width(&rollerSelectedStyle, LV_STATE_DEFAULT, 1);
        lv_style_set_border_color(&rollerSelectedStyle, LV_STATE_DEFAULT, LV_COLOR_BLACK);

        stylesInitialized = true;
    }
}

void ScreenClass::RegisterButtonPressedCallback(ButtonPressedCallback cb)
{
    buttonPressedCallback = cb;
}

void ScreenClass::NextButtonEventHandler(lv_obj_t *obj, lv_event_t event)
{
    ScreenClass *pScreen = (ScreenClass *)lv_obj_get_user_data(obj);

    switch (event)
    {
    case LV_EVENT_FOCUSED:
        lv_obj_set_style_local_text_color(pScreen->nextLabel, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
        break;
    case LV_EVENT_DEFOCUSED:
        lv_obj_set_style_local_text_color(pScreen->nextLabel, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
        break;
    case LV_EVENT_SHORT_CLICKED:
        if (pScreen->buttonPressedCallback)
        {
            pScreen->buttonPressedCallback(Screen_NextButtonPressed);
        }
        break;
    }
}

void ScreenClass::PreviousButtonEventHandler(lv_obj_t *obj, lv_event_t event)
{
    ScreenClass *pScreen = (ScreenClass *)lv_obj_get_user_data(obj);

    switch (event)
    {
    case LV_EVENT_FOCUSED:
        lv_obj_set_style_local_text_color(pScreen->previousLabel, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
        break;
    case LV_EVENT_DEFOCUSED:
        lv_obj_set_style_local_text_color(pScreen->previousLabel, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
        break;
    case LV_EVENT_SHORT_CLICKED:
        if (pScreen->buttonPressedCallback)
        {
            pScreen->buttonPressedCallback(Screen_PreviousButtonPressed);
        }
        break;
    }
}

/*
 Utility functions
 */

static const char dateTimeStringFormat[] = "MM/DD/YYYY hh:mm:ss AP";

void ScreenClass::GetTimeRemainingString(char *timeString, DateTime &currentTime, DateTime &alarmTime)
{
    DateTime alarmDateTime = ConvertAlarmToDate(currentTime, alarmTime);
    TimeSpan timeRemaining;

    if (currentTime > alarmDateTime)
    {
        timeRemaining = TimeSpan(0);
    }
    else
    {
        timeRemaining = alarmDateTime - currentTime;
    }

    if (timeRemaining.hours() > 0)
    {
        sprintf(timeString, "%d:%02d", timeRemaining.hours(), timeRemaining.minutes());
    }
    else if (timeRemaining.minutes() > 0)
    {
        sprintf(timeString, "%d:%02d", timeRemaining.minutes(), timeRemaining.seconds());
    }
    else
    {
        sprintf(timeString, "%d", timeRemaining.seconds());
    }
}

void ScreenClass::GetTimeString(char *pString, DateTime &datetime)
{
    sprintf(pString, "%d:%02d %s", datetime.twelveHour(), datetime.minute(), datetime.isPM() ? "PM" : "AM");
}
void ScreenClass::GetDateString(char *pString, DateTime &datetime)
{
    sprintf(pString, "%d/%d/%d", datetime.month(), datetime.day(), datetime.year());
}
