/*
    display.cpp

    A wrapper and interface file for the display and encoder

    Author: Rob Bultman
    License: MIT
*/

#include <Arduino.h>
#include <Encoder.h>
// #include <TeensyThreads.h>
#include <Bounce.h>
#include <SPI.h>
#include "display.h"
#include "ST7565.h"
#include "io_ports.h"

static lv_disp_drv_t displayDriver;
static lv_disp_t *pDisplayDevice;
static lv_disp_buf_t displayBuffer;
static lv_color_t buf_1[LV_HOR_RES_MAX * 10];
static lv_color_t buf_2[LV_HOR_RES_MAX * 10];

Bounce encoderButton(ENCODER_BUTTON, 50);
#define ENCODER_CENTER 16384
static Encoder encoder(2, 3);

static lv_indev_drv_t indev_drv;
static lv_indev_t *pInputDevice;

static void initializeEncoder()
{
  encoder.write(ENCODER_CENTER);
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
    digitalWrite(LCD_RESET, 0);
    delay(100);
    digitalWrite(LCD_RESET, 1);
    delay(100);
    for (i = 0; i < sizeof(initCmds) / sizeof(uint8_t); i++)
    {
      digitalWrite(LCD_DC, 0);
      SPI.transfer(initCmds[i]);
    }
}

#ifdef KILL
static void lvglTick(int unused)
{
  while (true)
  {
    threads.delay(5);
    lv_tick_inc(5);
  }
}

static void lvglTask(int unused)
{
  uint32_t nextTime = 5;
  
  while (true)
  {
    threads.delay(nextTime);
    nextTime = lv_task_handler();
  }
}
#endif

static volatile bool encoderButtonPressed = false;
static void UpdateEncoder()
{
  if (encoderButton.update())
  {
    if (encoderButton.risingEdge())
    {
      encoderButtonPressed = false;
    }
    else if (encoderButton.fallingEdge())
    {
      encoderButtonPressed = true;
    }
  }
}
#ifdef KILL
static void encoderButtonThread()
{
  while(true)
  {
    UpdateEncoder();
    threads.delay(10);
  }
}
#endif

#ifdef KILL
static bool encoder_read()
{
  int16_t pulses = encoder.read();
  int16_t steps = pulses / 4;

  if (steps != 0)
  {
    Serial.printf("Encoder: %d\r\n", steps);
    encoder.write(pulses - (steps * 4));
  }
  return false;
}
#endif
static bool encoder_read(lv_indev_drv_t *drv, lv_indev_data_t *data)
{
  int16_t pulses = encoder.read();
  int16_t steps = pulses / 4;

  data->enc_diff = 0;

  if (steps != 0)
  {
    data->enc_diff = steps;
    encoder.write(pulses - (steps * 4));
  }

  data->state = encoderButtonPressed ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;

  return false;
}

void Display_Initialize(void)
{
    initializeEncoder();
    lv_init();
    st7565_init();
    initLCD();

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

#ifdef KILL
    Serial.print("Starting lvglTick on ID ");
    Serial.println(threads.addThread(lvglTick, 1, 2048));
    Serial.print("Starting lvglTask on ID ");
    Serial.println(threads.addThread(lvglTask, 1, 16384));

    delay(1000);

    Serial.print("Starting encoderButtonThread on ID ");
    Serial.println(threads.addThread(encoderButtonThread));
#endif
}

lv_indev_t * Display_GetInputDevice()
{
    return pInputDevice;
}

void Display_Loop()
{
  static uint32_t lastMillis = 0;
  uint32_t newMillis = millis();
  uint32_t elapsed = newMillis - lastMillis;
  static uint8_t taskCount = 0;
  static uint8_t tickCount = 0;
  static uint32_t nextTaskCount = 5;

  tickCount += elapsed;
  taskCount += elapsed;

  if (tickCount >= 5)
  {
    lv_tick_inc(tickCount);
    tickCount = 0;
  }

  if (taskCount >= nextTaskCount)
  {
    nextTaskCount = lv_task_handler();
    taskCount = 0;
  }

  UpdateEncoder();
}