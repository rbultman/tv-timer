/*
    screen_class.cpp

    A utility class for screens.

    Author: Rob Bultman
    License: MIT
*/

#include "screen_class.h"

lv_style_t ScreenClass::menuButtonStyle;
lv_style_t ScreenClass::dialogButtonStyle;
lv_style_t ScreenClass::spinboxStyle;
lv_style_t ScreenClass::rollerStyle;
lv_style_t ScreenClass::rollerSelectedStyle;
bool ScreenClass::stylesInitialized = false;

ScreenClass::ScreenClass()
{
    scr = NULL;
    pInputDevice = NULL;
}

lv_obj_t *ScreenClass::CreateScreen(lv_indev_t *pInputDevice)
{
    this->pInputDevice = pInputDevice;

    InitializeStyles();

    if (scr)
    {
        lv_obj_del(scr);
    }
    // the main screen object
    scr = lv_obj_create(NULL, NULL);
    lv_obj_set_size(scr, LV_HOR_RES, LV_VER_RES);

    return scr;
}

void ScreenClass::InitializeStyles()
{
    if (!stylesInitialized)
    {
        // menu button default style
        lv_style_init(&menuButtonStyle);
        lv_style_set_border_width(&menuButtonStyle, LV_STATE_DEFAULT, 1);
        lv_style_set_border_color(&menuButtonStyle, LV_STATE_DEFAULT, LV_COLOR_BLACK);
        lv_style_set_bg_color(&menuButtonStyle, LV_STATE_DEFAULT, LV_COLOR_WHITE);
        lv_style_set_text_color(&menuButtonStyle, LV_STATE_DEFAULT, LV_COLOR_BLACK);
        lv_style_set_radius(&menuButtonStyle, LV_STATE_DEFAULT, 0);
        // focused style
        lv_style_set_border_width(&menuButtonStyle, LV_STATE_FOCUSED, 1);
        lv_style_set_border_color(&menuButtonStyle, LV_STATE_FOCUSED, LV_COLOR_WHITE);
        lv_style_set_bg_color(&menuButtonStyle, LV_STATE_FOCUSED, LV_COLOR_BLACK);
        lv_style_set_text_color(&menuButtonStyle, LV_STATE_FOCUSED, LV_COLOR_WHITE);
        lv_style_set_radius(&menuButtonStyle, LV_STATE_FOCUSED, 0);

        // dialog button default style
        lv_style_init(&dialogButtonStyle);
        lv_style_set_border_width(&dialogButtonStyle, LV_STATE_DEFAULT, 1);
        lv_style_set_border_color(&dialogButtonStyle, LV_STATE_DEFAULT, LV_COLOR_BLACK);
        lv_style_set_bg_color(&dialogButtonStyle, LV_STATE_DEFAULT, LV_COLOR_WHITE);
        lv_style_set_text_color(&dialogButtonStyle, LV_STATE_DEFAULT, LV_COLOR_BLACK);
        // focused style
        lv_style_set_border_width(&dialogButtonStyle, LV_STATE_FOCUSED, 1);
        lv_style_set_border_color(&dialogButtonStyle, LV_STATE_FOCUSED, LV_COLOR_WHITE);
        lv_style_set_bg_color(&dialogButtonStyle, LV_STATE_FOCUSED, LV_COLOR_BLACK);
        lv_style_set_text_color(&dialogButtonStyle, LV_STATE_FOCUSED, LV_COLOR_WHITE);

        // default style
        lv_style_init(&spinboxStyle);
        lv_style_set_border_width(&spinboxStyle, LV_STATE_DEFAULT, 1);
        lv_style_set_border_color(&spinboxStyle, LV_STATE_DEFAULT, LV_COLOR_BLACK);
        lv_style_set_bg_color(&spinboxStyle, LV_STATE_DEFAULT, LV_COLOR_WHITE);
        lv_style_set_text_color(&spinboxStyle, LV_STATE_DEFAULT, LV_COLOR_BLACK);
        lv_style_set_radius(&spinboxStyle, LV_STATE_DEFAULT, 0);
        // focused style
        lv_style_set_border_width(&spinboxStyle, LV_STATE_FOCUSED, 1);
        lv_style_set_border_color(&spinboxStyle, LV_STATE_FOCUSED, LV_COLOR_WHITE);
        lv_style_set_bg_color(&spinboxStyle, LV_STATE_FOCUSED, LV_COLOR_BLACK);
        lv_style_set_text_color(&spinboxStyle, LV_STATE_FOCUSED, LV_COLOR_WHITE);
        lv_style_set_radius(&spinboxStyle, LV_STATE_FOCUSED, 0);

        // roller style
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

        // roller selected style
        lv_style_init(&rollerSelectedStyle);
        lv_style_set_border_width(&rollerSelectedStyle, LV_STATE_DEFAULT, 1);
        lv_style_set_border_color(&rollerSelectedStyle, LV_STATE_DEFAULT, LV_COLOR_BLACK);

        stylesInitialized = true;
    }
}
