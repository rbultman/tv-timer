#include "io_ports.h"
#include "lvgl-iface.h"

extern "C" uint8_t LvglIface_spiReadByte(uint8_t data)
{
    uint8_t retval;

    spi.write((const char *)&data, 1, (char *)&retval, 1);
    return retval;
}

extern "C" void LvglIface_wait_us(uint32_t t)
{
    wait_us(t);
}

extern "C" void LvglIface_wait_ms(uint32_t t)
{
    ThisThread::sleep_for(std::chrono::milliseconds(t));
}

extern "C" void LvglIface_LcdCD(uint8_t val)
{
    lcdDC.write(val);
}

extern "C" void LvglIface_LcdReset(uint8_t val)
{
    lcdReset.write(val);
}

extern "C" void LvglIface_spiWrite(uint8_t val)
{
    spi.write(val);
}

extern "C" void LvglIface_spiWriteBytes(uint8_t *data, uint8_t n)
{
    spi.write((const char *)data, n, NULL, 0);
}
