#include <lvgl.h>
#include <SPI.h>
#include "io_ports.h"

void setup() {
  // put your setup code here, to run once:

  SPI.begin();

  pinMode(LCD_DC, OUTPUT);
  pinMode(LCD_RESET, OUTPUT);
  pinMode(LCD_BACKLIGHT_RED, OUTPUT);
  pinMode(LCD_BACKLIGHT_GREEN, OUTPUT);
  pinMode(LCD_BACKLIGHT_BLUE, OUTPUT);
  pinMode(ENCODER_BUTTON, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

}
