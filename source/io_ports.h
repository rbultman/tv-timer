/*
    Define the I/O pins here
*/

#ifndef IO_PORTS_H
#define IO_PORTS_H

#include "mbed.h"

#define LCD_DC D6
#define LCD_RESET D7
#define LCD_BACKLIGHT D8
#define ENCODER_BUTTON P1_8
#define RTC_SDA D14
#define RTC_SCL D15
extern SPI spi;
extern DigitalOut lcdDC;
extern DigitalOut lcdReset;
extern DigitalOut lcdBacklight;

#endif // IO_PORTS_H
