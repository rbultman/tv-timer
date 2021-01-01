/*
    menu_test.cpp

    A very simple screen to testing using an encoder with a menu.

    Author: Rob Bultman
    License: MIT
*/

#include <stdio.h>
#include <stdlib.h>
#include "menu_test.h"

lv_obj_t *Menu_Test::CreateScreen(lv_indev_t *pInputDevice)
{
    this->ScreenClass::CreateScreen(pInputDevice);

    label = lv_label_create(scr, NULL);             /*Create a label*/
    lv_obj_set_pos(label, 0, 0);                    /*Set its position*/
    lv_obj_set_size(label, LV_HOR_RES, LV_VER_RES); /*Set its size*/
    lv_label_set_text(label, "Menu");                /*Set the labels text*/

    lv_obj_t *btn1 = lv_btn_create(scr, NULL);
    lv_obj_add_style(btn1, LV_BTN_PART_MAIN, &menuButtonStyle);
    lv_obj_set_width(btn1, LV_HOR_RES);
    lv_obj_set_event_cb(btn1, event_handler);
    lv_obj_align(btn1, label, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);

    lv_obj_t *btn1label = lv_label_create(btn1, NULL);
    lv_label_set_text(btn1label, "Button 1");
    lv_obj_set_user_data(btn1, btn1label);

    lv_obj_t *btn2 = lv_btn_create(scr, btn1);
    lv_obj_align(btn2, btn1, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);

    lv_obj_t *btn2label = lv_label_create(btn2, btn1label);
    lv_label_set_text(btn2label, "Button 2");
    lv_obj_set_user_data(btn2, btn2label);

    lv_obj_t *btn3 = lv_btn_create(scr, btn1);
    lv_obj_align(btn3, btn2, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);

    lv_obj_t *btn3label = lv_label_create(btn3, btn1label);
    lv_label_set_text(btn3label, "Button 3");
    lv_obj_set_user_data(btn3, btn3label);

    group = lv_group_create();
    lv_group_add_obj(group, btn1);
    lv_group_add_obj(group, btn2);
    lv_group_add_obj(group, btn3);

    return scr;
}

static void event_handler(lv_obj_t *obj, lv_event_t event)
{
    lv_obj_t *pLabel;

    pLabel = (lv_obj_t *)lv_obj_get_user_data(obj);

    switch (event)
    {
    case LV_EVENT_CLICKED:
        printf("Clicked %p\n", obj);
        break;
    case LV_EVENT_FOCUSED:
        printf("Focused %p\r\n", obj);
        lv_obj_set_style_local_text_color(pLabel, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
        break;
    case LV_EVENT_DEFOCUSED:
        printf("Defocused %p\r\n", obj);
        lv_obj_set_style_local_text_color(pLabel, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
        break;
    case LV_EVENT_VALUE_CHANGED:
        printf("Toggled %p\n", obj);
        break;
    case LV_EVENT_PRESSED:
        printf("Pressed %p\n", obj);
        break;
    case LV_EVENT_SHORT_CLICKED:
        printf("Short click %p\n", obj);
        break;
    case LV_EVENT_RELEASED:
        printf("Released %p\n", obj);
        break;
    case LV_EVENT_LONG_PRESSED:
        printf("Long press %p\n", obj);
        break;
    case LV_EVENT_LONG_PRESSED_REPEAT:
        break;
    default:
        printf("Unhandled event %d for object %p\r\n", event, obj);
    }
}
