/*
    Define the I/O pins here
*/

#ifndef IO_PORTS_H
#define IO_PORTS_H

#include "mbed.h"

#define LCD_DC D6
#define LCD_RESET D7
#define LCD_BACKLIGHT D8

extern SPI spi;
extern DigitalOut lcdDC;
extern DigitalOut lcdReset;
extern DigitalOut lcdBacklight;

#endif // IO_PORTS_H
