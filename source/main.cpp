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

int main()
{
   while (true) 
   {
      greenLed = 1;
      ThisThread::sleep_for(BLINKING_RATE);
      
      greenLed = 0;
      ThisThread::sleep_for(BLINKING_RATE);
   }
}
