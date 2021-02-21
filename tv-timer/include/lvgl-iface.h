/*
    An interface to the LVGL library
*/

#ifndef LVGL_IFACE_H
#define LVGL_IFACE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif
    void LvglIface_wait_us(uint32_t t);
    void LvglIface_wait_ms(uint32_t t);
    void LvglIface_LcdCD(uint8_t val);
    void LvglIface_LcdReset(uint8_t val);
    void LvglIface_spiWrite(uint8_t val);
    uint8_t LvglIface_spiReadByte(uint8_t data);
    void LvglIface_spiWriteBytes(uint8_t *data, uint8_t n);
#ifdef __cplusplus
}
#endif

#endif // LVGL_IFACE_H
