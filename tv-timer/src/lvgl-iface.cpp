#include "io_ports.h"
#include "lvgl-iface.h"
#include <SPI.h>

extern "C" uint8_t LvglIface_spiReadByte(uint8_t data)
{
    uint8_t retval = 0;

//    spi.write((const char *)&data, 1, (char *)&retval, 1);
    return retval;
}

extern "C" void LvglIface_wait_us(uint32_t t)
{
    delayMicroseconds(t);
}

extern "C" void LvglIface_wait_ms(uint32_t t)
{
  delay(t);
}

extern "C" void LvglIface_LcdCD(uint8_t val)
{
    digitalWrite(LCD_DC, val);
}

extern "C" void LvglIface_LcdReset(uint8_t val)
{
    digitalWrite(LCD_RESET, val);
}

extern "C" void LvglIface_spiWrite(uint8_t val)
{
    SPI.transfer(val);
}

//extern "C" void LvglIface_spiWriteBytes(uint8_t *data, uint8_t n)
//{
//    spi.write((const char *)data, n, NULL, 0);
//}
