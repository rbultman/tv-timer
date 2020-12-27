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
#include "ds3231/ds3231.h"
#include "system_RZ_A1H.h"
#include "iodefine.h"
#include "mtu2_iobitmask.h"
extern "C" 
{
   #include "irq_ctrl.h"
}

DigitalOut redLed(LED1);
DigitalOut greenLed(LED2);
DigitalOut blueLed(LED3);
DigitalOut redLed2(LED4);
InterruptIn encoderButton(ENCODER_BUTTON);
#define ENCODER_CENTER 16384

SPI spi(D11, NC, D13, D10);
Ds3231 rtc(D14, D15);

static lv_indev_drv_t indev_drv;
static lv_indev_t *pInputDevice;

static lv_disp_drv_t displayDriver;
static lv_disp_t *pDisplayDevice;
static lv_disp_buf_t displayBuffer;
static lv_color_t buf_1[LV_HOR_RES_MAX * 10];
static lv_color_t buf_2[LV_HOR_RES_MAX * 10];

static volatile uint32_t seconds = 0;

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

static void event_handler(lv_obj_t *obj, lv_event_t event)
{
   lv_obj_t *pLabel;

   pLabel = (lv_obj_t * )lv_obj_get_user_data(obj);

   switch (event)
   {
   case LV_EVENT_CLICKED:
      printf("Clicked %p\n", obj);
      break;
   case LV_EVENT_FOCUSED:
      printf("Focused %p\r\n", obj);
      lv_obj_set_style_local_text_color(pLabel, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
      break;
   case LV_EVENT_DEFOCUSED:
      printf("Defocused %p\r\n", obj);
      lv_obj_set_style_local_text_color(pLabel, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
      break;
   case LV_EVENT_VALUE_CHANGED:
      printf("Toggled %p\n", obj);
      break;
   case LV_EVENT_PRESSED:
      printf("Pressed %p\n", obj);
      break;
   case LV_EVENT_SHORT_CLICKED:
      printf("Short click %p\n", obj);
      break;
   case LV_EVENT_RELEASED:
      printf("Released %p\n", obj);
      break;
   case LV_EVENT_LONG_PRESSED:
      printf("Long press %p\n", obj);
      break;
   case LV_EVENT_LONG_PRESSED_REPEAT:
      break;
   default:
      printf("Unhandled event %d for object %p\r\n", event, obj);
   }
}

lv_obj_t *label;
lv_group_t *group; 
lv_style_t menuButtonStyle;
lv_style_t menuButtonLabelStyle;
void showText(char *pText)
{
   label = lv_label_create(lv_scr_act(), NULL); /*Create a label*/
   lv_obj_set_pos(label, 0, 0);        /*Set its position*/
   lv_obj_set_size(label, LV_HOR_RES, LV_VER_RES);        /*Set its size*/
   lv_label_set_text(label, pText);                       /*Set the labels text*/

   // button default style
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

   // label style
   // lv_style_init(&menuButtonLabelStyle);
   // lv_style_set_text_color(&menuButtonLabelStyle, LV_STATE_DEFAULT, LV_COLOR_BLACK);
   // lv_style_set_text_color(&menuButtonLabelStyle, LV_STATE_FOCUSED, LV_COLOR_WHITE);
   // lv_style_set_text_sel_color(&menuButtonLabelStyle, LV_STATE_DEFAULT, LV_COLOR_BLACK);
   // lv_style_set_text_sel_color(&menuButtonLabelStyle, LV_STATE_FOCUSED, LV_COLOR_WHITE);

   lv_obj_t *btn1 = lv_btn_create(lv_scr_act(), NULL);
   lv_obj_add_style(btn1, LV_BTN_PART_MAIN, &menuButtonStyle);
   lv_obj_set_width(btn1, LV_HOR_RES);
   lv_obj_set_event_cb(btn1, event_handler);
   lv_obj_align(btn1, label, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);

   lv_obj_t *btn1label = lv_label_create(btn1, NULL);
   // lv_obj_add_style(btn1label, LV_LABEL_PART_MAIN, &menuButtonLabelStyle);
   lv_label_set_text(btn1label, "Button 1");
   lv_obj_set_user_data(btn1, btn1label);

   lv_obj_t *btn2 = lv_btn_create(lv_scr_act(), btn1);
   lv_obj_align(btn2, btn1, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);

   lv_obj_t *btn2label = lv_label_create(btn2, btn1label);
   lv_label_set_text(btn2label, "Button 2");
   lv_obj_set_user_data(btn2, btn2label);

   lv_obj_t *btn3 = lv_btn_create(lv_scr_act(), btn1);
   lv_obj_align(btn3, btn2, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);

   lv_obj_t *btn3label = lv_label_create(btn3, btn1label);
   lv_label_set_text(btn3label, "Button 3");
   lv_obj_set_user_data(btn3, btn3label);

   group = lv_group_create();
   lv_group_add_obj(group, btn1);
   lv_group_add_obj(group, btn2);
   lv_group_add_obj(group, btn3);
   lv_indev_set_group(pInputDevice, group);

   printf("Button layout: %d\r\n", lv_btn_get_layout(btn1));
   printf("Button height: %d\r\n", lv_obj_get_height(btn1));
   printf("Button width: %d\r\n", lv_obj_get_width(btn1));
   printf("Label height: %d\r\n", lv_obj_get_height(btn1label));
   printf("Label width: %d\r\n", lv_obj_get_width(btn1label));
   lv_color_t color = lv_obj_get_style_text_color(btn1label, LV_LABEL_PART_MAIN);
   printf("Label text color: %u\r\n", color.full);
   color = lv_obj_get_style_bg_color(btn1label, LV_LABEL_PART_MAIN);
   printf("Label background color: %u\r\n", color.full);
   color = lv_obj_get_style_border_color(btn1, LV_BTN_PART_MAIN);
   printf("Button border color: %u\r\n", color.full);
   color = LV_COLOR_WHITE;
   printf("White color: %u\r\n", color.full);
   color = LV_COLOR_BLACK;
   printf("Black color: %u\r\n", color.full);
   lv_style_int_t radius = lv_obj_get_style_radius(btn1, LV_BTN_PART_MAIN);
   printf("Button radius: %d\r\n", radius);
   printf("Label 1 pointer: %p\r\n", btn1label);
   printf("Label 2 pointer: %p\r\n", btn2label);
   printf("Label 3 pointer: %p\r\n", btn3label);
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

void RtcClockInputInterrupt();
static Thread heartbeatThread;
static void HeartbeatTask()
{
   while(true)
   {
      greenLed = 1;
      ThisThread::sleep_for(50ms);
      // printf("Seconds: %lu\r\n", seconds);

      greenLed = 0;
      ThisThread::sleep_for(950ms);
   }
}

static void initializeEncoder()
{
   // Set P1_0 and P1_10 to alt functions
   // Initialize MTU2
   // Enable clock to MTU2
   CPG.STBCR3 = CPG.STBCR3 & ~CPG_STBCR3_BIT_MSTP33;
   MTU2.TCNT_1 = ENCODER_CENTER;
   // set mode to phase counting
   MTU2.TMDR_1 = 0x04;

   uint16_t mask;
   mask = (1 << 10) | 1;
   GPIO.PIPC1 = GPIO.PIPC1 | mask;
   // set P1_0 to alt mode 3
   // set P1_10 to alt mode 4
   GPIO.PFCAE1 = GPIO.PFCAE1 & ~mask;
   GPIO.PFCE1 = GPIO.PFCE1 | mask;
   GPIO.PFC1 = GPIO.PFC1 | (1 << 10);
   GPIO.PMC1 = GPIO.PMC1 | mask;
   // start the timer
   MTU2.TSTR = MTU2.TSTR | 0x02;
}

void RtcClockInputInterrupt()
{
   MTU2.TSR_2 = MTU2.TSR_2 & ~MTU2_TSR_n_TGFA;
   seconds++;
}

DigitalIn rtcClockInput(P1_1, PullUp);
void InitRtcClockInput()
{
   // Enable clock to MTU2
   CPG.STBCR3 = CPG.STBCR3 & ~CPG_STBCR3_BIT_MSTP33;
   // Set Channel 2 TCNT input to TCLKC, reset by TGRA
   MTU2.TCR_2 = 0x26;
   // Reset TGRA after 1 second
   MTU2.TGRA_2 = 32768;
   // use alternate pin function
   GPIO.PIPC1 = GPIO.PIPC1 | 0x0002;
   // set P1_1 to alt mode 3
   GPIO.PFCAE1 = GPIO.PFCAE1 & ~0x0002;
   GPIO.PFCE1 = GPIO.PFCE1 | 0x0002;
   GPIO.PFC1 = GPIO.PFC1 & ~0x0002;
   GPIO.PMC1 = GPIO.PMC1 | 0x0002;
   // Install the interrupt handler
   uint32_t retval = InterruptHandlerRegister(TGI2A_IRQn, RtcClockInputInterrupt);
   if (retval == 0)
   {
      puts("IRQ for RTC clock successfully installed.");
   }
   else
   {
      puts("ERROR installing IRQ for RTC clock.");
   }
   // Enable the interrupt in MTU2
   MTU2.TIER_2 = MTU2.TIER_2 | MTU2_TIER_n_TGIEA;
   // Enable the IRQ at the core
   IRQ_Enable(TGI2A_IRQn);
   // start the timer
   MTU2.TSTR = MTU2.TSTR | 0x04;
}

static void InitClock()
{
   ds3231_time_t rtc_time;
   ds3231_calendar_t rtc_calendar;
   ds3231_cntl_stat_t rtc_control_status = {0, 0x08};

   rtc.set_cntl_stat_reg(rtc_control_status);
   rtc_calendar.day = 6;
   rtc_calendar.date = 25;
   rtc_calendar.month = 12;
   rtc_calendar.year = 20;
   rtc_time.mode = 1; // 12 hour mode
   rtc_time.am_pm = 1;
   rtc_time.hours = 1;
   rtc_time.minutes = 14;
   rtc_time.seconds = 0;

   //Set the time, uses inverted logic for return value
   if (rtc.set_time(rtc_time))
   {
      printf("\nrtc.set_time failed!!\n");
   }
   else
   {
      puts("RTC time set success.");
   }

   //Set the calendar, uses inverted logic for return value
   if (rtc.set_calendar(rtc_calendar))
   {
      printf("\nrtc.set_calendar failed!!\n");
   }
   else
   {
      puts("RTC date set success.");
   }
}

bool encoderButtonPressed = false;
void EncoderButtonDownHandler()
{
   encoderButtonPressed = true;
}

void EncoderButtonUpHandler()
{
   encoderButtonPressed = false;
}

bool encoder_read(lv_indev_drv_t *drv, lv_indev_data_t *data)
{
   int16_t encSteps = MTU2.TCNT_1 - ENCODER_CENTER;

   data->enc_diff = 0;

   if (encSteps/4 != 0)
   {
      data->enc_diff = encSteps/4;
      MTU2.TCNT_1 = ENCODER_CENTER;
   }

   data->state = encoderButtonPressed ? LV_INDEV_STATE_PR :
         LV_INDEV_STATE_REL;

         return false;
}

int main()
{
   printf("Starting...\r\n");

   initializeEncoder();
   InitClock();

   spi.frequency(10000000);

   lv_init();
   st7565_init();
   initLCD();

   lcdBacklight = 1;

   // create display driver
   lv_disp_buf_init(&displayBuffer, buf_1, buf_2, LV_HOR_RES_MAX * 10);
   lv_disp_drv_init(&displayDriver);
   displayDriver.buffer = &displayBuffer;
   displayDriver.flush_cb = st7565_flush;
   pDisplayDevice = lv_disp_drv_register(&displayDriver);

   // create input device driver
   lv_indev_drv_init(&indev_drv);
   indev_drv.type = LV_INDEV_TYPE_ENCODER;
   indev_drv.read_cb = encoder_read;
   pInputDevice = lv_indev_drv_register(&indev_drv);

   lvglTickThread.start(lvglTick);
   lvglTickThread.set_priority(osPriorityNormal1);

   lvglTaskThread.start(lvglTask);
   lvglTaskThread.set_priority(osPriorityNormal);

   ThisThread::sleep_for(1s);

   heartbeatThread.start(HeartbeatTask);
   InitRtcClockInput();

   encoderButton.fall(EncoderButtonDownHandler);
   encoderButton.rise(EncoderButtonUpHandler);

   lv_scr_load(Create());
   char msg[64] = "Menu";
   showText(msg);

   while (true)
   {
      ThisThread::sleep_for(33ms);
   }
}
