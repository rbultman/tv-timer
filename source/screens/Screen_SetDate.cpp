/*
    Screen_SetDate.h

    A screen to set the date.

    Author: Rob Bultman
    License: MIT
*/

#include <stdio.h>
#include "Screen_SetDate.h"

void Screen_SetDate::SpinboxEventHandler(lv_obj_t *obj, lv_event_t event)
{
    Screen_SetDate *pScreen = (Screen_SetDate *)lv_obj_get_user_data(obj);

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

void Screen_SetDate::ButtonEventHandler(lv_obj_t *obj, lv_event_t event)
{
    Screen_SetDate *pScreen = (Screen_SetDate *)lv_obj_get_user_data(obj);

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

void Screen_SetDate::RollerEventHandler(lv_obj_t *obj, lv_event_t event)
{
    Screen_SetDate *pScreen = (Screen_SetDate *)lv_obj_get_user_data(obj);
    uint16_t month;
    uint16_t * key;

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
        month = lv_roller_get_selected(pScreen->monthRoller);
        printf("Selected month: %d\n", month + 1);
        break;
    case LV_EVENT_KEY:
        key = (uint16_t * )lv_event_get_data();
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

lv_obj_t *Screen_SetDate::CreateScreen(lv_indev_t *pInputDevice)
{
    this->ScreenClass::CreateScreen(pInputDevice);

    lv_obj_t *header = lv_label_create(scr, NULL);
    lv_label_set_text(header, "Set Date");
    lv_obj_align(header, scr, LV_ALIGN_IN_TOP_MID, 0, 0);

    lv_obj_t * cont = lv_cont_create(scr, NULL);
    lv_obj_set_auto_realign(cont, true);
    lv_obj_set_height(cont, 27);
    lv_obj_align_origo(cont, scr, LV_ALIGN_CENTER, 0, 0);
    lv_cont_set_fit2(cont, LV_FIT_TIGHT, LV_FIT_NONE);
    lv_cont_set_layout(cont, LV_LAYOUT_ROW_MID);

    static lv_style_t rollerStyle;
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

    monthRoller = lv_roller_create(cont, NULL);
    lv_obj_add_style(monthRoller, LV_ROLLER_PART_BG, &rollerStyle);
    lv_obj_add_style(monthRoller, LV_ROLLER_PART_SELECTED, &rollerStyle);
    lv_roller_set_auto_fit(monthRoller, true);
    lv_roller_set_options(monthRoller,
                          "Jan\n"
                          "Feb\n"
                          "Mar\n"
                          "Apr\n"
                          "May\n"
                          "Jun\n"
                          "Jul\n"
                          "Aug\n"
                          "Sep\n"
                          "Oct\n"
                          "Nov\n"
                          "Dec",
                          LV_ROLLER_MODE_NORMAL);
    lv_roller_set_visible_row_count(monthRoller, 1);
    lv_obj_set_event_cb(monthRoller, RollerEventHandler);
    lv_obj_set_user_data(monthRoller, this);
    lv_obj_align_origo(monthRoller, scr, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_local_border_width(monthRoller, LV_ROLLER_PART_SELECTED, LV_STATE_DEFAULT, 1);
    lv_obj_set_style_local_border_color(monthRoller, LV_ROLLER_PART_SELECTED, LV_STATE_DEFAULT, LV_COLOR_BLACK);

    daySpinbox = lv_spinbox_create(cont, NULL);
    lv_obj_add_style(daySpinbox, LV_SPINBOX_PART_BG, &spinboxStyle);
    lv_spinbox_set_range(daySpinbox, 1, 12);
    lv_spinbox_set_digit_format(daySpinbox, 2, 0);
    lv_spinbox_set_step(daySpinbox, 1);
    lv_obj_set_event_cb(daySpinbox, SpinboxEventHandler);
    lv_obj_set_user_data(daySpinbox, this);
    lv_textarea_set_cursor_hidden(daySpinbox, true);
    lv_spinbox_step_prev(daySpinbox);
    lv_textarea_set_cursor_hidden(daySpinbox, true);
    lv_obj_set_width(daySpinbox, 24);

    yearSpinbox = lv_spinbox_create(cont, daySpinbox);
    lv_obj_set_user_data(yearSpinbox, this);
    lv_spinbox_set_digit_format(yearSpinbox, 4, 0);
    lv_spinbox_set_range(yearSpinbox, 2020, 2100);
    lv_obj_set_width(yearSpinbox, 40);

    acceptButton = lv_btn_create(scr, NULL);
    lv_obj_set_event_cb(acceptButton, ButtonEventHandler);
    lv_obj_set_width(acceptButton, 60);
    lv_obj_add_style(acceptButton, LV_BTN_PART_MAIN, &dialogButtonStyle);
    lv_obj_set_user_data(acceptButton, this);
    lv_obj_set_pos(acceptButton,
                   LV_HOR_RES - lv_obj_get_width(acceptButton),
                   LV_VER_RES - lv_obj_get_height(acceptButton));

    acceptLabel = lv_label_create(acceptButton, NULL);
    lv_label_set_text(acceptLabel, "Next");

    group = lv_group_create();
    lv_group_add_obj(group, monthRoller);
    lv_group_add_obj(group, daySpinbox);
    lv_group_add_obj(group, yearSpinbox);
    lv_group_add_obj(group, acceptButton);
    lv_indev_set_group(pInputDevice, group);

    return scr;
}
