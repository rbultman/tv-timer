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
        lv_spinbox_step_next(lv_group_get_focused(pScreen->group));
        break;
    case LV_EVENT_DEFOCUSED:
        lv_spinbox_step_next(lv_group_get_focused(pScreen->group));
        break;
    case LV_EVENT_SHORT_CLICKED:
        lv_group_set_editing(pScreen->group, false);
        break;
    case LV_EVENT_VALUE_CHANGED:
        if (obj == pScreen->minuteSpinbox)
        {
            pScreen->minutes = lv_spinbox_get_value(obj);
        }
        else
        {
            pScreen->hours = lv_spinbox_get_value(obj);
        }
        break;
    }
}

void Screen_SetTime::AmPmRollerEventHandler(lv_obj_t *obj, lv_event_t event)
{
    Screen_SetTime *pScreen = (Screen_SetTime *)lv_obj_get_user_data(obj);
    uint16_t amPm;

    switch (event)
    {
    case LV_EVENT_SHORT_CLICKED:
        lv_group_set_editing(pScreen->group, false);
        break;
    case LV_EVENT_VALUE_CHANGED:
        amPm = lv_roller_get_selected(pScreen->amPmRoller);
        pScreen->amPm = amPm;
        break;
    }
}

lv_obj_t *Screen_SetTime::CreateScreen(lv_indev_t *pInputDevice, bool hasNextButton, bool hasPreviousButton)
{
    this->ScreenClass::CreateScreen(pInputDevice, hasNextButton, hasPreviousButton);

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
    lv_spinbox_set_rollover(hourSpinbox, true);

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

    group = lv_group_create();
    lv_group_add_obj(group, hourSpinbox);
    lv_group_add_obj(group, minuteSpinbox);
    lv_group_add_obj(group, amPmRoller);
    if (hasNextButton)
        lv_group_add_obj(group, nextButton);
    if (hasPreviousButton)
        lv_group_add_obj(group, previousButton);

    return scr;
}

void Screen_SetTime::SetTime(DateTime &dt)
{
    this->hours = dt.twelveHour();
    this->minutes = dt.minute();
    this->amPm = dt.isPM();

    lv_spinbox_set_value(hourSpinbox, this->hours);
    lv_spinbox_set_value(minuteSpinbox, this->minutes);
    lv_roller_set_selected(amPmRoller, this->amPm, false);
}

void Screen_SetTime::GetTime(uint8_t *hours, uint8_t *minutes, uint8_t *amPm)
{
    *hours = this->hours;
    *minutes = this->minutes;
    *amPm = this->amPm;
}
