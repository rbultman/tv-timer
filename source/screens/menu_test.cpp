/*
    menu_test.cpp

    A very simple screen to testing using an encoder with a menu.

    Author: Rob Bultman
    License: MIT
*/

#include <stdio.h>
#include <stdlib.h>
#include "menu_test.h"

static lv_indev_t *pInputDevice = NULL;

lv_obj_t *MenuTest_CreateScreen(lv_indev_t *_pInputDevice)
{
    static lv_obj_t *scr = NULL;
    pInputDevice = _pInputDevice;

    if (scr)
    {
        lv_obj_del(scr);
    }
    // the main screen object
    scr = lv_obj_create(NULL, NULL);
    lv_obj_set_size(scr, LV_HOR_RES, LV_VER_RES);

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

static lv_obj_t *label;
static lv_group_t *group;
static lv_style_t menuButtonStyle;
void MenuTest_ShowMenu(char *pText)
{
    label = lv_label_create(lv_scr_act(), NULL);    /*Create a label*/
    lv_obj_set_pos(label, 0, 0);                    /*Set its position*/
    lv_obj_set_size(label, LV_HOR_RES, LV_VER_RES); /*Set its size*/
    lv_label_set_text(label, pText);                /*Set the labels text*/

    // button default style
    lv_style_init(&menuButtonStyle);
    lv_style_set_border_width(&menuButtonStyle, LV_STATE_DEFAULT, 1);
    lv_style_set_border_color(&menuButtonStyle, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_style_set_bg_color(&menuButtonStyle, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_style_set_text_color(&menuButtonStyle, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_style_set_radius(&menuButtonStyle, LV_STATE_DEFAULT, 0);
    lv_style_set_text_font(&menuButtonStyle, LV_STATE_DEFAULT, &jetbrains_light_14);
    // focused style
    lv_style_set_border_width(&menuButtonStyle, LV_STATE_FOCUSED, 1);
    lv_style_set_border_color(&menuButtonStyle, LV_STATE_FOCUSED, LV_COLOR_WHITE);
    lv_style_set_bg_color(&menuButtonStyle, LV_STATE_FOCUSED, LV_COLOR_BLACK);
    lv_style_set_text_color(&menuButtonStyle, LV_STATE_FOCUSED, LV_COLOR_WHITE);
    lv_style_set_radius(&menuButtonStyle, LV_STATE_FOCUSED, 0);
    lv_style_set_text_font(&menuButtonStyle, LV_STATE_FOCUSED, &jetbrains_light_14);

    lv_obj_t *btn1 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_add_style(btn1, LV_BTN_PART_MAIN, &menuButtonStyle);
    lv_obj_set_width(btn1, LV_HOR_RES);
    lv_obj_set_event_cb(btn1, event_handler);
    lv_obj_align(btn1, label, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);

    lv_obj_t *btn1label = lv_label_create(btn1, NULL);
    lv_label_set_text(btn1label, "Button 1");
    lv_obj_set_user_data(btn1, btn1label);

    lv_obj_t *btn2 = lv_btn_create(lv_scr_act(), btn1);
    lv_obj_align(btn2, btn1, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);

    lv_obj_t *btn2label = lv_label_create(btn2, btn1label);
    lv_label_set_text(btn2label, "Button 2");
    lv_obj_set_user_data(btn2, btn2label);

    lv_obj_t *btn3 = lv_btn_create(lv_scr_act(), btn1);
    lv_obj_align(btn3, btn2, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);

    lv_obj_t *btn3label = lv_label_create(btn3, btn1label);
    lv_label_set_text(btn3label, "Button 3");
    lv_obj_set_user_data(btn3, btn3label);

    group = lv_group_create();
    lv_group_add_obj(group, btn1);
    lv_group_add_obj(group, btn2);
    lv_group_add_obj(group, btn3);
    lv_indev_set_group(pInputDevice, group);

    printf("Button layout: %d\r\n", lv_btn_get_layout(btn1));
    printf("Button height: %d\r\n", lv_obj_get_height(btn1));
    printf("Button width: %d\r\n", lv_obj_get_width(btn1));
    printf("Label height: %d\r\n", lv_obj_get_height(btn1label));
    printf("Label width: %d\r\n", lv_obj_get_width(btn1label));
    lv_color_t color = lv_obj_get_style_text_color(btn1label, LV_LABEL_PART_MAIN);
    printf("Label text color: %u\r\n", color.full);
    color = lv_obj_get_style_bg_color(btn1label, LV_LABEL_PART_MAIN);
    printf("Label background color: %u\r\n", color.full);
    color = lv_obj_get_style_border_color(btn1, LV_BTN_PART_MAIN);
    printf("Button border color: %u\r\n", color.full);
    color = LV_COLOR_WHITE;
    printf("White color: %u\r\n", color.full);
    color = LV_COLOR_BLACK;
    printf("Black color: %u\r\n", color.full);
    lv_style_int_t radius = lv_obj_get_style_radius(btn1, LV_BTN_PART_MAIN);
    printf("Button radius: %d\r\n", radius);
    printf("Label 1 pointer: %p\r\n", btn1label);
    printf("Label 2 pointer: %p\r\n", btn2label);
    printf("Label 3 pointer: %p\r\n", btn3label);
}