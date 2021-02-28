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
        lv_spinbox_step_next(lv_group_get_focused(pScreen->group));
        break;
    case LV_EVENT_SHORT_CLICKED:
        lv_group_set_editing(pScreen->group, false);
        break;
    case LV_EVENT_VALUE_CHANGED:
        if (obj == pScreen->yearSpinbox)
        {
            pScreen->year = lv_spinbox_get_value(obj);
        }
        else
        {
            pScreen->day = lv_spinbox_get_value(obj);
        }
        break;
    }
}

void Screen_SetDate::RollerEventHandler(lv_obj_t *obj, lv_event_t event)
{
    Screen_SetDate *pScreen = (Screen_SetDate *)lv_obj_get_user_data(obj);
    uint16_t month;

    switch (event)
    {
    case LV_EVENT_SHORT_CLICKED:
        lv_group_set_editing(pScreen->group, false);
        break;
    case LV_EVENT_VALUE_CHANGED:
        month = lv_roller_get_selected(pScreen->monthRoller);
        pScreen->month = month;
        break;
    }
}

lv_obj_t *Screen_SetDate::CreateScreen(lv_indev_t *pInputDevice, bool hasNextButton, bool hasPreviousButton)
{
    this->ScreenClass::CreateScreen(pInputDevice, hasNextButton, hasPreviousButton);

    lv_obj_t *header = lv_label_create(scr, NULL);
    lv_label_set_text(header, "Set Date");
    lv_obj_align(header, scr, LV_ALIGN_IN_TOP_MID, 0, 0);

    lv_obj_t * cont = lv_cont_create(scr, NULL);
    lv_obj_set_auto_realign(cont, true);
    lv_obj_set_height(cont, 27);
    lv_obj_align_origo(cont, scr, LV_ALIGN_CENTER, 0, 0);
    lv_cont_set_fit2(cont, LV_FIT_TIGHT, LV_FIT_NONE);
    lv_cont_set_layout(cont, LV_LAYOUT_ROW_MID);

    monthRoller = lv_roller_create(cont, NULL);
    lv_obj_add_style(monthRoller, LV_ROLLER_PART_BG, &rollerStyle);
    lv_obj_add_style(monthRoller, LV_ROLLER_PART_SELECTED, &rollerStyle);
    lv_obj_add_style(monthRoller, LV_ROLLER_PART_SELECTED, &rollerSelectedStyle);
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
                          LV_ROLLER_MODE_INFINITE);
    lv_roller_set_visible_row_count(monthRoller, 1);
    lv_obj_set_event_cb(monthRoller, RollerEventHandler);
    lv_obj_set_user_data(monthRoller, this);
    lv_obj_align_origo(monthRoller, scr, LV_ALIGN_CENTER, 0, 0);

    daySpinbox = lv_spinbox_create(cont, NULL);
    lv_obj_add_style(daySpinbox, LV_SPINBOX_PART_BG, &spinboxStyle);
    lv_spinbox_set_range(daySpinbox, 1, 31);
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

    group = lv_group_create();
    lv_group_add_obj(group, monthRoller);
    lv_group_add_obj(group, daySpinbox);
    lv_group_add_obj(group, yearSpinbox);
    if (hasNextButton)
        lv_group_add_obj(group, nextButton);
    if (hasPreviousButton)
        lv_group_add_obj(group, previousButton);

    return scr;
}

void Screen_SetDate::SetDate(uint8_t month, uint8_t day, uint16_t year)
{
    this->month = month;
    this->day = day;
    this->year = year;

    lv_roller_set_selected(monthRoller, month, false);
    lv_spinbox_set_value(daySpinbox, day);
    lv_spinbox_set_value(yearSpinbox, year);
}

void Screen_SetDate::GetDate(uint8_t *month, uint8_t *day, uint16_t *year)
{
    *month = this->month;
    *day = this->day;
    *year = this->year;
}
