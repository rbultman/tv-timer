/*
    screen_class.h

    A utility class for screens.

    Author: Rob Bultman
    License: MIT
*/

#ifndef SCREEN_CLASS_H
#define SCREEN_CLASS_H

#include "lvgl.h"

enum 
{
    Screen_PreviousButtonPressed,
    Screen_NextButtonPressed,
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

    protected:
        lv_obj_t *scr;
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
        static lv_indev_t *pInputDevice;
        static lv_style_t menuButtonStyle;
        static lv_style_t dialogButtonStyle;
        static lv_style_t spinboxStyle;
        static lv_style_t rollerStyle;
        static lv_style_t rollerSelectedStyle;
        static bool stylesInitialized;
};

#endif // SCREEN_CLASS_H
