#include "lvgl/lvgl.h"

/*******************************************************************************
 * Size: 12 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifndef JETBRAINS_REGULAR_12
#define JETBRAINS_REGULAR_12 1
#endif

#if JETBRAINS_REGULAR_12

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t gylph_bitmap[] = {
    /* U+20 " " */
    0x0,

    /* U+21 "!" */
    0xaa, 0xa0, 0xc0,

    /* U+22 "\"" */
    0x99, 0x99,

    /* U+23 "#" */
    0x24, 0x49, 0xf9, 0x22, 0x85, 0x3f, 0x24, 0x48,

    /* U+24 "$" */
    0x21, 0x1d, 0x5a, 0xd1, 0xc7, 0x2d, 0x7e, 0x42,
    0x0,

    /* U+25 "%" */
    0xe3, 0x4a, 0xa7, 0x41, 0x7, 0xcc, 0xa9, 0x9e,

    /* U+26 "&" */
    0x31, 0x24, 0x18, 0x62, 0x59, 0xa6, 0x74,

    /* U+27 "'" */
    0xf0,

    /* U+28 "(" */
    0x13, 0x48, 0x88, 0x88, 0x88, 0x47, 0x10,

    /* U+29 ")" */
    0x8c, 0x21, 0x11, 0x11, 0x11, 0x2c, 0x80,

    /* U+2A "*" */
    0x10, 0x23, 0x59, 0xc2, 0x8d, 0x80,

    /* U+2B "+" */
    0x20, 0x82, 0x3f, 0x20, 0x80,

    /* U+2C "," */
    0x4b, 0x40,

    /* U+2D "-" */
    0xf8,

    /* U+2E "." */
    0xf0,

    /* U+2F "/" */
    0x8, 0x44, 0x21, 0x10, 0x8c, 0x42, 0x31, 0x0,

    /* U+30 "0" */
    0x74, 0x63, 0x1a, 0xc6, 0x31, 0x70,

    /* U+31 "1" */
    0x65, 0x8, 0x42, 0x10, 0x84, 0xf8,

    /* U+32 "2" */
    0x74, 0x62, 0x11, 0x19, 0x98, 0xf8,

    /* U+33 "3" */
    0xf8, 0x88, 0x60, 0x86, 0x31, 0x70,

    /* U+34 "4" */
    0x11, 0x88, 0x84, 0xc7, 0xe1, 0x8,

    /* U+35 "5" */
    0xfc, 0x21, 0xe8, 0x84, 0x31, 0x70,

    /* U+36 "6" */
    0x10, 0x82, 0x1e, 0xce, 0x18, 0x73, 0x78,

    /* U+37 "7" */
    0xfe, 0x20, 0x86, 0x10, 0x42, 0x8, 0x60,

    /* U+38 "8" */
    0x74, 0x63, 0x17, 0x46, 0x31, 0x70,

    /* U+39 "9" */
    0x7b, 0x38, 0x61, 0xcd, 0xe1, 0x4, 0x20,

    /* U+3A ":" */
    0xf0, 0x3c,

    /* U+3B ";" */
    0x6c, 0x0, 0xd2, 0x40,

    /* U+3C "<" */
    0x1b, 0x21, 0x83, 0x4,

    /* U+3D "=" */
    0xf8, 0x1, 0xf0,

    /* U+3E ">" */
    0xc1, 0x86, 0x36, 0x40,

    /* U+3F "?" */
    0xf0, 0x42, 0x37, 0x21, 0x0, 0x60,

    /* U+40 "@" */
    0x7b, 0x18, 0x6f, 0xa6, 0x9a, 0x6f, 0x83, 0x7,
    0x0,

    /* U+41 "A" */
    0x21, 0x45, 0x14, 0x53, 0x2f, 0xa2, 0x88,

    /* U+42 "B" */
    0xf4, 0x63, 0x1f, 0x46, 0x31, 0xf0,

    /* U+43 "C" */
    0x74, 0x63, 0x8, 0x42, 0x31, 0x70,

    /* U+44 "D" */
    0xf4, 0x63, 0x18, 0xc6, 0x31, 0xf0,

    /* U+45 "E" */
    0xfc, 0x21, 0xf, 0xc2, 0x10, 0xf8,

    /* U+46 "F" */
    0xfc, 0x21, 0xf, 0xc2, 0x10, 0x80,

    /* U+47 "G" */
    0x74, 0x61, 0xb, 0xc6, 0x31, 0x70,

    /* U+48 "H" */
    0x8c, 0x63, 0x1f, 0xc6, 0x31, 0x88,

    /* U+49 "I" */
    0xf9, 0x8, 0x42, 0x10, 0x84, 0xf8,

    /* U+4A "J" */
    0x38, 0x42, 0x10, 0x86, 0x31, 0x70,

    /* U+4B "K" */
    0x8a, 0x29, 0x24, 0xe2, 0x49, 0x22, 0x88,

    /* U+4C "L" */
    0x84, 0x21, 0x8, 0x42, 0x10, 0xf8,

    /* U+4D "M" */
    0x8e, 0xf7, 0xba, 0xc6, 0x31, 0x88,

    /* U+4E "N" */
    0xce, 0x73, 0x5a, 0xd6, 0x73, 0x98,

    /* U+4F "O" */
    0x74, 0x63, 0x18, 0xc6, 0x31, 0x70,

    /* U+50 "P" */
    0xf4, 0x63, 0x1f, 0x42, 0x10, 0x80,

    /* U+51 "Q" */
    0x74, 0x63, 0x18, 0xc6, 0x31, 0x70, 0x82,

    /* U+52 "R" */
    0xf4, 0x63, 0x1f, 0x4a, 0x53, 0x88,

    /* U+53 "S" */
    0x74, 0x61, 0x87, 0x4, 0x31, 0x70,

    /* U+54 "T" */
    0xfc, 0x82, 0x8, 0x20, 0x82, 0x8, 0x20,

    /* U+55 "U" */
    0x8c, 0x63, 0x18, 0xc6, 0x31, 0x70,

    /* U+56 "V" */
    0x8a, 0x28, 0xb2, 0x51, 0x45, 0x1c, 0x20,

    /* U+57 "W" */
    0x93, 0x66, 0xcb, 0x66, 0xcd, 0x9b, 0x36, 0x6c,

    /* U+58 "X" */
    0x44, 0xc8, 0xa1, 0xc1, 0x7, 0xa, 0x22, 0x44,

    /* U+59 "Y" */
    0x44, 0x88, 0xa1, 0x43, 0x82, 0x4, 0x8, 0x10,

    /* U+5A "Z" */
    0xf8, 0x44, 0x62, 0x31, 0x10, 0xf8,

    /* U+5B "[" */
    0xf2, 0x49, 0x24, 0x92, 0x70,

    /* U+5C "\\" */
    0x86, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10,

    /* U+5D "]" */
    0xe4, 0x92, 0x49, 0x24, 0xf0,

    /* U+5E "^" */
    0x22, 0x94, 0x98, 0x80,

    /* U+5F "_" */
    0xf8,

    /* U+60 "`" */
    0x48,

    /* U+61 "a" */
    0x76, 0x42, 0xf8, 0xc5, 0xe0,

    /* U+62 "b" */
    0x84, 0x2d, 0x98, 0xc6, 0x31, 0xf0,

    /* U+63 "c" */
    0x74, 0x61, 0x8, 0x45, 0xc0,

    /* U+64 "d" */
    0x8, 0x5f, 0x18, 0xc6, 0x31, 0x78,

    /* U+65 "e" */
    0x74, 0x63, 0xf8, 0x45, 0xc0,

    /* U+66 "f" */
    0x3c, 0x8f, 0xc8, 0x20, 0x82, 0x8, 0x20,

    /* U+67 "g" */
    0x7c, 0x63, 0x18, 0xbc, 0x21, 0x70,

    /* U+68 "h" */
    0x84, 0x3d, 0x18, 0xc6, 0x31, 0x88,

    /* U+69 "i" */
    0x30, 0xe, 0x8, 0x20, 0x82, 0x8, 0xfc,

    /* U+6A "j" */
    0x18, 0x1c, 0x21, 0x8, 0x42, 0x10, 0xb8,

    /* U+6B "k" */
    0x84, 0x23, 0x2b, 0x72, 0xd2, 0x88,

    /* U+6C "l" */
    0xe0, 0x82, 0x8, 0x20, 0x82, 0x8, 0x1c,

    /* U+6D "m" */
    0xfe, 0x9a, 0x69, 0xa6, 0x9a, 0x40,

    /* U+6E "n" */
    0xf4, 0x63, 0x18, 0xc6, 0x20,

    /* U+6F "o" */
    0x74, 0x63, 0x18, 0xc5, 0xc0,

    /* U+70 "p" */
    0xf4, 0x63, 0x18, 0xc7, 0xd0, 0x80,

    /* U+71 "q" */
    0x6c, 0xe3, 0x18, 0xc5, 0xe1, 0x8,

    /* U+72 "r" */
    0xf4, 0x63, 0x8, 0x42, 0x0,

    /* U+73 "s" */
    0x74, 0x60, 0xe0, 0xc5, 0xc0,

    /* U+74 "t" */
    0x20, 0x8f, 0xc8, 0x20, 0x82, 0x8, 0x3c,

    /* U+75 "u" */
    0x8c, 0x63, 0x18, 0xc5, 0xc0,

    /* U+76 "v" */
    0x8c, 0x72, 0xa5, 0x28, 0x80,

    /* U+77 "w" */
    0x92, 0xa5, 0xd3, 0x66, 0xcd, 0x9b, 0x0,

    /* U+78 "x" */
    0x89, 0x47, 0x8, 0x51, 0x68, 0x80,

    /* U+79 "y" */
    0x8c, 0x56, 0xa5, 0x18, 0x84, 0x60,

    /* U+7A "z" */
    0xf8, 0xc4, 0x44, 0x63, 0xe0,

    /* U+7B "{" */
    0xc, 0x41, 0x4, 0x10, 0x4e, 0x4, 0x10, 0x41,
    0x3,

    /* U+7C "|" */
    0xff, 0xf0,

    /* U+7D "}" */
    0xc0, 0x82, 0x8, 0x20, 0x81, 0xc8, 0x20, 0x82,
    0x30,

    /* U+7E "~" */
    0xe6, 0xd9, 0x80
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 115, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 115, .box_w = 2, .box_h = 9, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 115, .box_w = 4, .box_h = 4, .ofs_x = 2, .ofs_y = 5},
    {.bitmap_index = 6, .adv_w = 115, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 14, .adv_w = 115, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 23, .adv_w = 115, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 31, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 38, .adv_w = 115, .box_w = 1, .box_h = 4, .ofs_x = 3, .ofs_y = 5},
    {.bitmap_index = 39, .adv_w = 115, .box_w = 4, .box_h = 13, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 46, .adv_w = 115, .box_w = 4, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 53, .adv_w = 115, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 59, .adv_w = 115, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 64, .adv_w = 115, .box_w = 3, .box_h = 4, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 66, .adv_w = 115, .box_w = 5, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 67, .adv_w = 115, .box_w = 2, .box_h = 2, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 68, .adv_w = 115, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 76, .adv_w = 115, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 82, .adv_w = 115, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 88, .adv_w = 115, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 94, .adv_w = 115, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 100, .adv_w = 115, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 106, .adv_w = 115, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 112, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 119, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 126, .adv_w = 115, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 132, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 139, .adv_w = 115, .box_w = 2, .box_h = 7, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 141, .adv_w = 115, .box_w = 3, .box_h = 9, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 145, .adv_w = 115, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 149, .adv_w = 115, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 152, .adv_w = 115, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 156, .adv_w = 115, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 162, .adv_w = 115, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 171, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 178, .adv_w = 115, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 184, .adv_w = 115, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 190, .adv_w = 115, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 196, .adv_w = 115, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 202, .adv_w = 115, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 208, .adv_w = 115, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 214, .adv_w = 115, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 220, .adv_w = 115, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 226, .adv_w = 115, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 232, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 239, .adv_w = 115, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 245, .adv_w = 115, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 251, .adv_w = 115, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 257, .adv_w = 115, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 263, .adv_w = 115, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 269, .adv_w = 115, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 276, .adv_w = 115, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 282, .adv_w = 115, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 288, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 295, .adv_w = 115, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 301, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 308, .adv_w = 115, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 316, .adv_w = 115, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 324, .adv_w = 115, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 332, .adv_w = 115, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 338, .adv_w = 115, .box_w = 3, .box_h = 12, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 343, .adv_w = 115, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 351, .adv_w = 115, .box_w = 3, .box_h = 12, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 356, .adv_w = 115, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 360, .adv_w = 115, .box_w = 5, .box_h = 1, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 361, .adv_w = 115, .box_w = 3, .box_h = 2, .ofs_x = 2, .ofs_y = 8},
    {.bitmap_index = 362, .adv_w = 115, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 367, .adv_w = 115, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 373, .adv_w = 115, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 378, .adv_w = 115, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 384, .adv_w = 115, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 389, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 396, .adv_w = 115, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 402, .adv_w = 115, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 408, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 415, .adv_w = 115, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 422, .adv_w = 115, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 428, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 435, .adv_w = 115, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 441, .adv_w = 115, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 446, .adv_w = 115, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 451, .adv_w = 115, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 457, .adv_w = 115, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 463, .adv_w = 115, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 468, .adv_w = 115, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 473, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 480, .adv_w = 115, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 485, .adv_w = 115, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 490, .adv_w = 115, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 497, .adv_w = 115, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 503, .adv_w = 115, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 509, .adv_w = 115, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 514, .adv_w = 115, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 523, .adv_w = 115, .box_w = 1, .box_h = 12, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 525, .adv_w = 115, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 534, .adv_w = 115, .box_w = 6, .box_h = 3, .ofs_x = 1, .ofs_y = 3}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

/*Store all the custom data of the font*/
static lv_font_fmt_txt_dsc_t font_dsc = {
    .glyph_bitmap = gylph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
lv_font_t jetbrains_regular_12 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 13,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0)
    .underline_position = -2,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if JETBRAINS_REGULAR_12*/

