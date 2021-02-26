/*
    screen_class.h

    A utility class for screens.

    Author: Rob Bultman
    License: MIT
*/

#ifndef SCREEN_CLASS_H
#define SCREEN_CLASS_H

#include <ctime>
#include <time.h>
#include "lvgl.h"
#include "RTClib.h"

enum
{
    Screen_PreviousButtonPressed,
    Screen_NextButtonPressed,
    Screen_Menu1Pressed,
    Screen_Menu2Pressed,
    Screen_TimeoutComplete,
};

// Define callback functions
typedef void (*ButtonPressedCallback)(uint8_t whichButton);

class ScreenClass 
{
    public:
        ScreenClass();
        lv_obj_t *CreateScreen(lv_indev_t *pInputDevice, bool hasNextButton = false, bool hasPreviousButton = false);
        void LoadScreen();
        void RegisterButtonPressedCallback(ButtonPressedCallback cb);

        lv_obj_t *scr;

    protected:
        ButtonPressedCallback buttonPressedCallback;
        bool hasNextButton;
        bool hasPreviousButton;
        lv_obj_t *nextButton;
        lv_obj_t *nextLabel;
        lv_obj_t *previousButton;
        lv_obj_t *previousLabel;
        lv_group_t *group;
        void InitializeStyles();
        static void NextButtonEventHandler(lv_obj_t *obj, lv_event_t event);
        static void PreviousButtonEventHandler(lv_obj_t *obj, lv_event_t event);
        static void GetTimeRemainingString(char *timeString, DateTime &currentEpoch, DateTime &alarmTime);
        static void GetTimeString(char *pString, DateTime &t);
        static void GetDateString(char *pString, DateTime &t);
        static lv_indev_t *pInputDevice;
        static lv_style_t menuButtonStyle;
        static lv_style_t dialogButtonStyle;
        static lv_style_t spinboxStyle;
        static lv_style_t rollerStyle;
        static lv_style_t rollerSelectedStyle;
        static bool stylesInitialized;
};

#endif // SCREEN_CLASS_H
