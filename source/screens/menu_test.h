/*
    menu_test.h

    Author: Rob Bultman
    License: MIT
*/

#ifndef MENU_TEST_H
#define MENU_TEST_H

#include "lvgl.h"
#include "screen_class.h"

class Menu_Test : public ScreenClass
{
    public:
        lv_obj_t *CreateScreen(lv_indev_t *pInputDevice);
        void ShowMenu(char *pText);

    private:
        lv_obj_t *label;
        lv_group_t *group;
        lv_style_t menuButtonStyle;
};

#endif // MENU_TEST_H
