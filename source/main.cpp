/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdint.h>
#include "mbed.h"

// Blinking rate in milliseconds
#define BLINKING_RATE     1000ms

DigitalOut redLed(LED1);
DigitalOut greenLed(LED2);
DigitalOut blueLed(LED3);
DigitalOut redLed2(LED4);
DigitalOut lcdCS(D10);
DigitalOut lcdDC(D9);
DigitalOut lcdReset(D8);
DigitalOut lcdBacklight(D5);
DigitalOut touchCS(D7);
DigitalIn  touchInt(D6);

SPI spi(D11, D12, D13);

int main()
{
   while (true) 
   {
      greenLed = 1;
      lcdBacklight = 1;
      ThisThread::sleep_for(BLINKING_RATE);
      
      greenLed = 0;
      lcdBacklight = 0;
      ThisThread::sleep_for(BLINKING_RATE);
   }
}
