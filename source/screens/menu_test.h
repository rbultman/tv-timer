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

    private:
        static void event_handler(lv_obj_t *obj, lv_event_t event);
        lv_obj_t *label;
};

#endif // MENU_TEST_H
