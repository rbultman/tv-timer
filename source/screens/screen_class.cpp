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
    lv_scr_load(scr);
    lv_indev_set_group(pInputDevice, group);
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

void ScreenClass::GetTimeRemainingString(char *timeString, time_t currentEpoch, ds3231_alrm_t &alarmTime)
{
    struct tm alarmTimeStruct;
    time_t alarmTimeEpoch;
    struct tm currentTimeStruct;
    time_t timeRemaining;
    time_t hours;
    time_t minutes;
    time_t seconds;

    currentTimeStruct = *localtime(&currentEpoch);
    alarmTimeStruct = currentTimeStruct;
    alarmTimeStruct.tm_hour = alarmTime.hours;
    alarmTimeStruct.tm_min = alarmTime.minutes;
    alarmTimeStruct.tm_sec = alarmTime.seconds;
    alarmTimeStruct.tm_mday = alarmTime.date;
    if (alarmTime.date < (uint32_t)currentTimeStruct.tm_mday)
    {
        alarmTimeStruct.tm_mon++;
        if (alarmTimeStruct.tm_mon >= 12)
        {
            alarmTimeStruct.tm_year++;
            alarmTimeStruct.tm_mon = 0;
        }
    }

    alarmTimeEpoch = mktime(&alarmTimeStruct);
    if (alarmTimeEpoch < currentEpoch)
    {
        timeRemaining = 0;
    }
    else
    {
        timeRemaining = alarmTimeEpoch - currentEpoch;
    }

    hours = timeRemaining / 3600;
    minutes = (timeRemaining % 3600) / 60;
    seconds = (timeRemaining % 3600) % 60;
    if (hours > 0)
    {
        sprintf(timeString, "%llu:%02llu", hours, minutes);
    }
    else if (minutes > 0)
    {
        sprintf(timeString, "%llu:%02llu", minutes, seconds);
    }
    else
    {
        sprintf(timeString, "%llu", seconds);
    }
}

void ScreenClass::GetTimeString(char *pString, time_t epoch)
{
    struct tm ts;
    static const char pm[] = "PM";
    static const char am[] = "AM";
    const char *amPm = am;

    ts = *localtime(&epoch);
    if (ts.tm_hour > 12)
    {
        ts.tm_hour -= 12;
        amPm = pm;
    }
    if (ts.tm_hour == 0)
    {
        ts.tm_hour = 12;
    }

    sprintf(pString, "%d:%02d %s", ts.tm_hour, ts.tm_min, amPm);
}
void ScreenClass::GetDateString(char *pString, time_t epoch)
{
    struct tm ts;

    ts = *localtime(&epoch);
    sprintf(pString, "%d/%d/%d", ts.tm_mon + 1, ts.tm_mday, ts.tm_year + 1900);
}
