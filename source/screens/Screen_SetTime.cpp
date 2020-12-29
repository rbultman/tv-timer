/*
    Screen_SetTime.cpp

    A screen to set the date.

    Author: Rob Bultman
    License: MIT
*/

#include <stdio.h>
#include "Screen_SetTime.h"

void Screen_SetTime::SpinboxEventHandler(lv_obj_t *obj, lv_event_t event)
{
    Screen_SetTime *pScreen = (Screen_SetTime *)lv_obj_get_user_data(obj);

    switch (event)
    {
    case LV_EVENT_FOCUSED:
        printf("Focused %p\r\n", obj);
        lv_spinbox_step_next(lv_group_get_focused(pScreen->group));
        break;
    case LV_EVENT_SHORT_CLICKED:
        printf("Short click %p\n", obj);
        lv_group_set_editing(pScreen->group, false);
        break;
    }
}

void Screen_SetTime::AcceptButtonEventHandler(lv_obj_t *obj, lv_event_t event)
{
    Screen_SetTime *pScreen = (Screen_SetTime *)lv_obj_get_user_data(obj);

    switch (event)
    {
    case LV_EVENT_FOCUSED:
        puts("Button received focus, exiting editing mode.");
        lv_obj_set_style_local_text_color(pScreen->acceptLabel, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
        break;
    case LV_EVENT_DEFOCUSED:
        printf("Button defocused %p\r\n", obj);
        lv_obj_set_style_local_text_color(pScreen->acceptLabel, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
        break;
    case LV_EVENT_SHORT_CLICKED:
        printf("Button short click\n");
        break;
    }
}

void Screen_SetTime::PreviousButtonEventHandler(lv_obj_t *obj, lv_event_t event)
{
    Screen_SetTime *pScreen = (Screen_SetTime *)lv_obj_get_user_data(obj);

    switch (event)
    {
    case LV_EVENT_FOCUSED:
        puts("Previous button received focus, exiting editing mode.");
        lv_obj_set_style_local_text_color(pScreen->previousLabel, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
        break;
    case LV_EVENT_DEFOCUSED:
        printf("Previous button defocused %p\r\n", obj);
        lv_obj_set_style_local_text_color(pScreen->previousLabel, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
        break;
    case LV_EVENT_SHORT_CLICKED:
        printf("Previous button short click\n");
        break;
    }
}

void Screen_SetTime::AmPmRollerEventHandler(lv_obj_t *obj, lv_event_t event)
{
    Screen_SetTime *pScreen = (Screen_SetTime *)lv_obj_get_user_data(obj);
    uint16_t month;
    uint16_t *key;

    switch (event)
    {
    case LV_EVENT_FOCUSED:
        puts("Roller received focus.");
        break;
    case LV_EVENT_DEFOCUSED:
        printf("Roller defocused\r\n");
        break;
    case LV_EVENT_SHORT_CLICKED:
        printf("Roller short click\n");
        lv_group_set_editing(pScreen->group, false);
        break;
    case LV_EVENT_VALUE_CHANGED:
        month = lv_roller_get_selected(pScreen->amPmRoller);
        printf("Selected month: %d\n", month + 1);
        break;
    case LV_EVENT_KEY:
        key = (uint16_t *)lv_event_get_data();
        printf("Roller key pressed: %d\r\n", *key);
        if (*key == LV_KEY_LEFT)
        {
            puts("Left key pressed");
        }
        if (*key == LV_KEY_RIGHT)
        {
            puts("Right key pressed");
        }
        break;
    default:
        printf("Unhandled roller event: %d\r\n", event);
        break;
    }
}

lv_obj_t *Screen_SetTime::CreateScreen(lv_indev_t *pInputDevice)
{
    this->ScreenClass::CreateScreen(pInputDevice);

    lv_obj_t *header = lv_label_create(scr, NULL);
    lv_label_set_text(header, "Set Time");
    lv_obj_align(header, scr, LV_ALIGN_IN_TOP_MID, 0, 0);

    lv_obj_t * cont = lv_cont_create(scr, NULL);
    lv_obj_set_auto_realign(cont, true);
    lv_obj_set_height(cont, 27);
    lv_obj_align_origo(cont, scr, LV_ALIGN_CENTER, 0, 0);
    lv_cont_set_fit2(cont, LV_FIT_TIGHT, LV_FIT_NONE);
    lv_cont_set_layout(cont, LV_LAYOUT_ROW_MID);

    hourSpinbox = lv_spinbox_create(cont, NULL);
    lv_obj_add_style(hourSpinbox, LV_SPINBOX_PART_BG, &spinboxStyle);
    lv_spinbox_set_range(hourSpinbox, 1, 12);
    lv_spinbox_set_digit_format(hourSpinbox, 2, 0);
    lv_spinbox_set_step(hourSpinbox, 1);
    lv_obj_set_event_cb(hourSpinbox, SpinboxEventHandler);
    lv_obj_set_user_data(hourSpinbox, this);
    lv_textarea_set_cursor_hidden(hourSpinbox, true);
    lv_spinbox_step_prev(hourSpinbox);
    lv_textarea_set_cursor_hidden(hourSpinbox, true);
    lv_obj_set_width(hourSpinbox, 24);

    lv_obj_t *colon = lv_label_create(cont, NULL);
    lv_label_set_text(colon, ":");

    minuteSpinbox = lv_spinbox_create(cont, hourSpinbox);
    lv_obj_set_user_data(minuteSpinbox, this);
    lv_spinbox_set_digit_format(minuteSpinbox, 2, 0);
    lv_spinbox_set_range(minuteSpinbox, 0, 59);
    lv_obj_set_width(minuteSpinbox, 24);
    lv_spinbox_set_rollover(minuteSpinbox, true);

    amPmRoller = lv_roller_create(cont, NULL);
    lv_obj_add_style(amPmRoller, LV_ROLLER_PART_BG, &rollerStyle);
    lv_obj_add_style(amPmRoller, LV_ROLLER_PART_SELECTED, &rollerStyle);
    lv_obj_add_style(amPmRoller, LV_ROLLER_PART_SELECTED, &rollerSelectedStyle);
    lv_roller_set_auto_fit(amPmRoller, true);
    lv_roller_set_options(amPmRoller,
                          "AM\n"
                          "PM",
                          LV_ROLLER_MODE_NORMAL);
    lv_roller_set_visible_row_count(amPmRoller, 1);
    lv_obj_set_event_cb(amPmRoller, AmPmRollerEventHandler);
    lv_obj_set_user_data(amPmRoller, this);
    lv_obj_align_origo(amPmRoller, scr, LV_ALIGN_CENTER, 0, 0);

    acceptButton = lv_btn_create(scr, NULL);
    lv_obj_set_event_cb(acceptButton, AcceptButtonEventHandler);
    lv_obj_set_width(acceptButton, 60);
    lv_obj_add_style(acceptButton, LV_BTN_PART_MAIN, &dialogButtonStyle);
    lv_obj_set_user_data(acceptButton, this);
    lv_obj_set_pos(acceptButton,
                   LV_HOR_RES - lv_obj_get_width(acceptButton),
                   LV_VER_RES - lv_obj_get_height(acceptButton));

    acceptLabel = lv_label_create(acceptButton, NULL);
    lv_label_set_text(acceptLabel, "Next");

    previousButton = lv_btn_create(scr, NULL);
    lv_obj_set_event_cb(previousButton, AcceptButtonEventHandler);
    lv_obj_set_width(previousButton, 60);
    lv_obj_add_style(previousButton, LV_BTN_PART_MAIN, &dialogButtonStyle);
    lv_obj_set_user_data(previousButton, this);
    lv_obj_set_pos(previousButton,
                   0,
                   LV_VER_RES - lv_obj_get_height(acceptButton));

    previousLabel = lv_label_create(previousButton, NULL);
    lv_obj_set_event_cb(previousButton, PreviousButtonEventHandler);
    lv_label_set_text(previousLabel, "Prev");

    group = lv_group_create();
    lv_group_add_obj(group, hourSpinbox);
    lv_group_add_obj(group, minuteSpinbox);
    lv_group_add_obj(group, amPmRoller);
    lv_group_add_obj(group, acceptButton);
    lv_group_add_obj(group, previousButton);
    lv_indev_set_group(pInputDevice, group);

    return scr;
}
