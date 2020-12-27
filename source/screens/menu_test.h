/*
    menu_test.h

    Author: Rob Bultman
    License: MIT
*/

#ifndef MENU_TEST_H
#define MENU_TEST_H

#include "lvgl.h"

lv_obj_t *MenuTest_CreateScreen(lv_indev_t *pInputDevice);
void MenuTest_ShowMenu(char *pText);

#endif // MENU_TEST_H
