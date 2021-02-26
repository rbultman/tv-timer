/*
    backlight.cpp

    Handle the backlight
*/

#include <Arduino.h>
#include "io_ports.h"
#include "backlight.h"

void BacklighOn()
{
    digitalWrite(LCD_BACKLIGHT_RED, 1);
    digitalWrite(LCD_BACKLIGHT_GREEN, 1);
    digitalWrite(LCD_BACKLIGHT_BLUE, 1);
}

void BacklightOff()
{
    digitalWrite(LCD_BACKLIGHT_RED, 0);
    digitalWrite(LCD_BACKLIGHT_GREEN, 0);
    digitalWrite(LCD_BACKLIGHT_BLUE, 0);
}
