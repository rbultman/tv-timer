/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "mbed.h"
#include "io_ports.h"
#include "lvgl.h"
#include "ST7565.h"

// Blinking rate in milliseconds
#define BLINKING_RATE     1000ms

DigitalOut redLed(LED1);
DigitalOut greenLed(LED2);
DigitalOut blueLed(LED3);
DigitalOut redLed2(LED4);

SPI spi(D11, NC, D13, D10);

static lv_indev_drv_t indev_drv;
static lv_indev_t *pInputDevice;

static lv_disp_drv_t displayDriver;
static lv_disp_t *pDisplayDevice;
static lv_disp_buf_t displayBuffer;
static lv_color_t buf_1[LV_HOR_RES_MAX * 10];
static lv_color_t buf_2[LV_HOR_RES_MAX * 10];

static Thread lvglTickThread;

static void lvglTick()
{
   while (true)
   {
      ThisThread::sleep_for(5ms);
      lv_tick_inc(5);
   }
}

static Thread lvglTaskThread;

static void lvglTask()
{
   while (true)
   {
      ThisThread::sleep_for(5ms);
      lv_task_handler();
   }
}

static void btn_event_cb(lv_obj_t *btn, lv_event_t event)
{
   if (event == LV_EVENT_CLICKED)
   {
      static uint8_t cnt = 0;
      cnt++;

      /*Get the first child of the button which is the label and change its text*/
      lv_obj_t *label = lv_obj_get_child(btn, NULL);
      lv_label_set_text_fmt(label, "Button: %d", cnt);
   }
}

/**
 * Create a button with a label and react on Click event.
 */
void lv_ex_get_started_1(void)
{
   lv_obj_t *btn = lv_btn_create(lv_scr_act(), NULL); /*Add a button the current screen*/
   lv_obj_set_pos(btn, 10, 10);                       /*Set its position*/
   lv_obj_set_size(btn, 120, 50);                     /*Set its size*/
   lv_obj_set_event_cb(btn, btn_event_cb);            /*Assign a callback to the button*/

   lv_obj_t *label = lv_label_create(btn, NULL); /*Add a label to the button*/
   lv_label_set_text(label, "Button");           /*Set the labels text*/
}

void showText(char *pText)
{
   lv_obj_t *label = lv_label_create(lv_scr_act(), NULL); /*Create a label*/
   lv_obj_set_pos(label, 0, 5);                           /*Set its position*/
   lv_obj_set_size(label, LV_HOR_RES, LV_VER_RES);        /*Set its size*/
   lv_label_set_text(label, pText);                       /*Set the labels text*/
}

static lv_obj_t *scr = NULL;
static lv_obj_t *Create(void)
{
   if (scr)
   {
      lv_obj_del(scr);
   }
   // the main screen object
   scr = lv_obj_create(NULL, NULL);
   lv_obj_set_size(scr, LV_HOR_RES, LV_VER_RES);
   // lv_obj_set_style(scr, &lv_style_plain_color);

   // screen title
   // lv_obj_t *title = lv_label_create(scr, NULL);
   // lv_label_set_style(title, GetStylePointer(Style_RedMediumMessageTextModel));
   // lv_label_set_text(title, "ERRORS");
   // lv_obj_align(title, NULL, LV_ALIGN_IN_TOP_MID, 0, 10);

   // error list
   // errorList = lv_page_create(scr, NULL);
   // lv_page_set_scrl_layout(errorList, LV_LAYOUT_COL_M);
   // lv_page_set_sb_mode(errorList, LV_SB_MODE_AUTO);
   // lv_obj_set_size(errorList, 240, 320 - 80 - 20);
   // lv_obj_align(errorList, title, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
   // lv_obj_refresh_style(errorList);

   // AddErrorsToList();

   // create the refresh button
   // lv_obj_t *btn1 = lv_btn_create(scr, NULL);
   // lv_obj_set_width(btn1, 240 - 20);
   // lv_obj_align(btn1, errorList, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
   // lv_btn_set_action(btn1, LV_BTN_ACTION_CLICK, RefreshErrorMessages);
   /*Add a label to the button*/
   // lv_obj_t *label = lv_label_create(btn1, NULL);
   // lv_label_set_text(label, "Refresh Errors");

   return scr;
}

static void initLCD()
{
   const uint8_t initCmds[] =
       {
           0xA0, // ADC select normal
           0xAE, // display off
           0xC0, // common output mode select normal
           0xA2, // LCD bias 1/9
           0x2F, // Internal power operating mode
           0x26, // select resistor ratio
           0x81, // Set V5 output voltage
           0x11, // Column addres set upper bit
           0xAF, // Display on
       };
   uint8_t i;
   lcdReset = 0;
   ThisThread::sleep_for(100ms);
   lcdReset = 1;
   ThisThread::sleep_for(100ms);
   for (i = 0; i < sizeof(initCmds) / sizeof(uint8_t); i++)
   {
      lcdDC = 0;
      spi.write(initCmds[i]);
   }
}

int main()
{
   printf("Starting...\r\n");

   spi.frequency(10000000);

   lv_init();
   st7565_init();
   initLCD();

   lcdBacklight = 0;

#ifdef KILL
   lv_indev_drv_init(&indev_drv);
   indev_drv.read_cb = xpt2046_read;
   pInputDevice = lv_indev_drv_register(&indev_drv);
#endif

   lv_disp_buf_init(&displayBuffer, buf_1, buf_2, LV_HOR_RES_MAX * 10);

   lv_disp_drv_init(&displayDriver);
   displayDriver.buffer = &displayBuffer;
   displayDriver.flush_cb = st7565_flush;
   pDisplayDevice = lv_disp_drv_register(&displayDriver);

   lvglTickThread.start(lvglTick);
   lvglTickThread.set_priority(osPriorityNormal1);

   lvglTaskThread.start(lvglTask);
   lvglTaskThread.set_priority(osPriorityNormal);

   ThisThread::sleep_for(1s);

//   lv_scr_load(Create());
  lv_ex_get_started_1();

  // Set P1_0 and P1_10 to alt functions
  // Initialize MTU2
  CPG.STBCR3 = CPG.STBCR3 & ~CPG_STBCR3_BIT_MSTP33;
  MTU2.TCNT_1 = 0;
  MTU2.TMDR_1 = 0x04;

  uint16_t mask;
  mask = (1 << 10) | 1;
  printf("PMC1 mask: 0x%04x\r\n", mask);
  GPIO.PIPC1 = GPIO.PIPC1 | mask;
  // set P1_0 to alt mode 3
  // set P1_10 to alt mode 4
  GPIO.PFCAE1 = GPIO.PFCAE1 & ~mask;
  GPIO.PFCE1 = GPIO.PFCE1 | mask;
  GPIO.PFC1 = GPIO.PFC1 | (1<<10);
  GPIO.PMC1 = GPIO.PMC1 | mask;
  // start the timer
  MTU2.TSTR = MTU2.TSTR | 0x02;

  printf("TMDR 1: 0x%02x\r\n", MTU2.TMDR_1);
  printf("PMC1:   0x%04x\r\n", GPIO.PMC1);
  printf("PIPC1:  0x%04x\r\n", GPIO.PIPC1);
  printf("PFCAE1: 0x%04x\r\n", GPIO.PFCAE1);
  printf("PFCE1:  0x%04x\r\n", GPIO.PFCE1);
  printf("PFC1:   0x%04x\r\n", GPIO.PFC1);
  printf("TSTR:   0x%02x\r\n", MTU2.TSTR);

  int count = 0;
  while (true)
  {
      greenLed = 1;
      ThisThread::sleep_for(20ms);

      char msg[64] ;
      sprintf(msg, "%5d", MTU2.TCNT_1);
      lv_scr_load(Create());
      showText(msg);

      greenLed = 0;
      ThisThread::sleep_for(20ms);
   }
}
