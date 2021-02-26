#include "lvgl/lvgl.h"

/*******************************************************************************
 * Size: 14 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifndef JETBRAINS_LIGHT_14
#define JETBRAINS_LIGHT_14 1
#endif

#if JETBRAINS_LIGHT_14

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t gylph_bitmap[] = {
    /* U+20 " " */
    0x0,

    /* U+21 "!" */
    0xaa, 0xa8, 0x30,

    /* U+22 "\"" */
    0x99, 0x99,

    /* U+23 "#" */
    0x12, 0x12, 0x7f, 0x24, 0x24, 0x24, 0xfe, 0x44,
    0x44, 0x48,

    /* U+24 "$" */
    0x10, 0x41, 0x1e, 0x96, 0x59, 0x1c, 0x18, 0x59,
    0x65, 0x78, 0x41, 0x0,

    /* U+25 "%" */
    0xf1, 0x92, 0x94, 0xf4, 0x8, 0x16, 0x29, 0x29,
    0x49, 0x86,

    /* U+26 "&" */
    0x38, 0x89, 0x2, 0x6, 0x12, 0x63, 0x42, 0x8c,
    0xe4,

    /* U+27 "'" */
    0xf0,

    /* U+28 "(" */
    0x16, 0x48, 0x88, 0x88, 0x88, 0x84, 0x21,

    /* U+29 ")" */
    0x86, 0x21, 0x11, 0x11, 0x11, 0x12, 0x48,

    /* U+2A "*" */
    0x10, 0x22, 0x4b, 0xe3, 0x5, 0x11, 0x0,

    /* U+2B "+" */
    0x10, 0x23, 0xf8, 0x81, 0x2, 0x0,

    /* U+2C "," */
    0x7a, 0x80,

    /* U+2D "-" */
    0xfc,

    /* U+2E "." */
    0xf0,

    /* U+2F "/" */
    0x4, 0x10, 0x82, 0x8, 0x41, 0x4, 0x20, 0x86,
    0x10, 0x42, 0x0,

    /* U+30 "0" */
    0x7b, 0x38, 0x61, 0xa6, 0x98, 0x61, 0xcd, 0xe0,

    /* U+31 "1" */
    0x33, 0x41, 0x4, 0x10, 0x41, 0x4, 0x13, 0xf0,

    /* U+32 "2" */
    0x7b, 0x38, 0x41, 0x8, 0x21, 0x8, 0x43, 0xf0,

    /* U+33 "3" */
    0xfc, 0x21, 0xe, 0xc, 0x10, 0x61, 0xcd, 0xe0,

    /* U+34 "4" */
    0x8, 0x41, 0x8, 0x47, 0x18, 0x7f, 0x4, 0x10,

    /* U+35 "5" */
    0xfe, 0x8, 0x2e, 0xcc, 0x10, 0x61, 0x8d, 0xe0,

    /* U+36 "6" */
    0x10, 0x82, 0x1e, 0x4e, 0x18, 0x61, 0xcd, 0xe0,

    /* U+37 "7" */
    0xff, 0xa, 0x10, 0x40, 0x81, 0x4, 0x8, 0x20,
    0x40,

    /* U+38 "8" */
    0x7a, 0x18, 0x61, 0x7b, 0x38, 0x61, 0xcd, 0xe0,

    /* U+39 "9" */
    0x7b, 0x38, 0x61, 0xcd, 0xe0, 0x84, 0x10, 0x80,

    /* U+3A ":" */
    0xf0, 0xf,

    /* U+3B ";" */
    0x6c, 0x0, 0x1a, 0x4a, 0x0,

    /* U+3C "<" */
    0xc, 0xc4, 0x20, 0x60, 0x60, 0x40,

    /* U+3D "=" */
    0xfc, 0x0, 0x3f,

    /* U+3E ">" */
    0xc0, 0xc0, 0x81, 0x19, 0x88, 0x0,

    /* U+3F "?" */
    0xf0, 0x42, 0x37, 0x21, 0x0, 0x3, 0x0,

    /* U+40 "@" */
    0x38, 0x8a, 0xc, 0x79, 0x32, 0x64, 0xc9, 0x93,
    0x1e, 0x2, 0x3, 0x80,

    /* U+41 "A" */
    0x30, 0x60, 0xc2, 0x44, 0x89, 0x1f, 0x42, 0x85,
    0x8,

    /* U+42 "B" */
    0xfa, 0x18, 0x61, 0xfa, 0x38, 0x61, 0x8f, 0xe0,

    /* U+43 "C" */
    0x7b, 0x38, 0x60, 0x82, 0x8, 0x21, 0xcd, 0xe0,

    /* U+44 "D" */
    0xfa, 0x38, 0x61, 0x86, 0x18, 0x61, 0x8f, 0xe0,

    /* U+45 "E" */
    0xfe, 0x8, 0x20, 0xfa, 0x8, 0x20, 0x83, 0xf0,

    /* U+46 "F" */
    0xfe, 0x8, 0x20, 0xfe, 0x8, 0x20, 0x82, 0x0,

    /* U+47 "G" */
    0x7b, 0x38, 0x60, 0x82, 0x78, 0x61, 0xcd, 0xe0,

    /* U+48 "H" */
    0x86, 0x18, 0x61, 0xfe, 0x18, 0x61, 0x86, 0x10,

    /* U+49 "I" */
    0xf9, 0x8, 0x42, 0x10, 0x84, 0x27, 0xc0,

    /* U+4A "J" */
    0x1c, 0x10, 0x41, 0x4, 0x10, 0x61, 0xcd, 0xe0,

    /* U+4B "K" */
    0x86, 0x28, 0xa4, 0xf2, 0x48, 0xa2, 0x86, 0x10,

    /* U+4C "L" */
    0x82, 0x8, 0x20, 0x82, 0x8, 0x20, 0x83, 0xf0,

    /* U+4D "M" */
    0xcf, 0x3c, 0xed, 0xb6, 0x58, 0x61, 0x86, 0x10,

    /* U+4E "N" */
    0xc7, 0x1c, 0x69, 0xa6, 0x59, 0x65, 0x8e, 0x30,

    /* U+4F "O" */
    0x7b, 0x38, 0x61, 0x86, 0x18, 0x61, 0x8d, 0xe0,

    /* U+50 "P" */
    0xfa, 0x38, 0x61, 0x8f, 0xe8, 0x20, 0x82, 0x0,

    /* U+51 "Q" */
    0x7b, 0x38, 0x61, 0x86, 0x18, 0x61, 0xcd, 0xe0,
    0x82, 0x4,

    /* U+52 "R" */
    0xfa, 0x18, 0x61, 0xfa, 0x49, 0x22, 0x8a, 0x10,

    /* U+53 "S" */
    0x7a, 0x38, 0x60, 0x60, 0x60, 0x61, 0xcd, 0xe0,

    /* U+54 "T" */
    0xfe, 0x20, 0x40, 0x81, 0x2, 0x4, 0x8, 0x10,
    0x20,

    /* U+55 "U" */
    0x86, 0x18, 0x61, 0x86, 0x18, 0x61, 0xcd, 0xe0,

    /* U+56 "V" */
    0x85, 0xa, 0x12, 0x24, 0x89, 0xa, 0x14, 0x30,
    0x60,

    /* U+57 "W" */
    0x89, 0x59, 0x59, 0x5a, 0x5a, 0x5a, 0x66, 0x66,
    0x66, 0x26,

    /* U+58 "X" */
    0x84, 0x89, 0x21, 0x43, 0x6, 0xa, 0x24, 0x45,
    0x8,

    /* U+59 "Y" */
    0x82, 0x89, 0x11, 0x42, 0x82, 0x4, 0x8, 0x10,
    0x20,

    /* U+5A "Z" */
    0xfc, 0x20, 0x84, 0x10, 0x84, 0x10, 0x83, 0xf0,

    /* U+5B "[" */
    0xf2, 0x49, 0x24, 0x92, 0x49, 0xc0,

    /* U+5C "\\" */
    0x81, 0x4, 0x10, 0x20, 0x82, 0x4, 0x10, 0x20,
    0x82, 0x4, 0x10,

    /* U+5D "]" */
    0xe4, 0x92, 0x49, 0x24, 0x93, 0xc0,

    /* U+5E "^" */
    0x10, 0xc2, 0x92, 0x4a, 0x10,

    /* U+5F "_" */
    0xfe,

    /* U+60 "`" */
    0x90,

    /* U+61 "a" */
    0x79, 0x10, 0x5f, 0x86, 0x18, 0xdd,

    /* U+62 "b" */
    0x82, 0xb, 0xb3, 0x86, 0x18, 0x61, 0xce, 0xe0,

    /* U+63 "c" */
    0x7b, 0x38, 0x60, 0x82, 0x1c, 0xde,

    /* U+64 "d" */
    0x4, 0x17, 0x73, 0x86, 0x18, 0x61, 0xcd, 0xd0,

    /* U+65 "e" */
    0x7a, 0x18, 0x7f, 0x82, 0xc, 0xde,

    /* U+66 "f" */
    0x3c, 0x8f, 0xc8, 0x20, 0x82, 0x8, 0x20, 0x80,

    /* U+67 "g" */
    0x77, 0x38, 0x61, 0x86, 0x1c, 0xdd, 0x4, 0x17,
    0x80,

    /* U+68 "h" */
    0x82, 0xb, 0xb3, 0x86, 0x18, 0x61, 0x86, 0x10,

    /* U+69 "i" */
    0x30, 0xf, 0x4, 0x10, 0x41, 0x4, 0x13, 0xf0,

    /* U+6A "j" */
    0x18, 0x3c, 0x21, 0x8, 0x42, 0x10, 0x84, 0x2e,
    0x0,

    /* U+6B "k" */
    0x82, 0x8, 0x62, 0x93, 0xc9, 0x22, 0x8a, 0x10,

    /* U+6C "l" */
    0xe0, 0x40, 0x81, 0x2, 0x4, 0x8, 0x10, 0x20,
    0x3c,

    /* U+6D "m" */
    0xef, 0x26, 0x4c, 0x99, 0x32, 0x64, 0xc9,

    /* U+6E "n" */
    0xbb, 0x38, 0x61, 0x86, 0x18, 0x61,

    /* U+6F "o" */
    0x7b, 0x38, 0x61, 0x86, 0x1c, 0xde,

    /* U+70 "p" */
    0xbb, 0x38, 0x61, 0x86, 0x1c, 0xee, 0x82, 0x8,
    0x0,

    /* U+71 "q" */
    0x77, 0x38, 0x61, 0x86, 0x1c, 0xdd, 0x4, 0x10,
    0x40,

    /* U+72 "r" */
    0xbb, 0x38, 0x60, 0x82, 0x8, 0x20,

    /* U+73 "s" */
    0x7a, 0x18, 0x18, 0x1c, 0x18, 0x5e,

    /* U+74 "t" */
    0x20, 0x8f, 0xc8, 0x20, 0x82, 0x8, 0x20, 0xf0,

    /* U+75 "u" */
    0x86, 0x18, 0x61, 0x86, 0x1c, 0xde,

    /* U+76 "v" */
    0x86, 0x14, 0x52, 0x48, 0xa3, 0xc,

    /* U+77 "w" */
    0x93, 0x66, 0xd5, 0xab, 0x59, 0xb3, 0x26,

    /* U+78 "x" */
    0xc5, 0x22, 0x8c, 0x30, 0xa4, 0xa1,

    /* U+79 "y" */
    0x85, 0x14, 0x52, 0x28, 0xa3, 0x4, 0x10, 0x82,
    0x0,

    /* U+7A "z" */
    0xfc, 0x21, 0x4, 0x21, 0x8, 0x3f,

    /* U+7B "{" */
    0xc, 0x41, 0x4, 0x10, 0x41, 0x38, 0x10, 0x41,
    0x4, 0x10, 0x30,

    /* U+7C "|" */
    0xff, 0xfc,

    /* U+7D "}" */
    0xc0, 0x82, 0x8, 0x20, 0x82, 0x7, 0x20, 0x82,
    0x8, 0x23, 0x0,

    /* U+7E "~" */
    0xe6, 0x99, 0xc0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 134, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 134, .box_w = 2, .box_h = 10, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 134, .box_w = 4, .box_h = 4, .ofs_x = 2, .ofs_y = 6},
    {.bitmap_index = 6, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 16, .adv_w = 134, .box_w = 6, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 28, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 38, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 47, .adv_w = 134, .box_w = 1, .box_h = 4, .ofs_x = 4, .ofs_y = 6},
    {.bitmap_index = 48, .adv_w = 134, .box_w = 4, .box_h = 14, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 55, .adv_w = 134, .box_w = 4, .box_h = 14, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 62, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 69, .adv_w = 134, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 75, .adv_w = 134, .box_w = 2, .box_h = 5, .ofs_x = 3, .ofs_y = -3},
    {.bitmap_index = 77, .adv_w = 134, .box_w = 6, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 78, .adv_w = 134, .box_w = 2, .box_h = 2, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 79, .adv_w = 134, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 90, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 98, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 106, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 114, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 122, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 130, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 138, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 146, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 155, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 163, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 171, .adv_w = 134, .box_w = 2, .box_h = 8, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 173, .adv_w = 134, .box_w = 3, .box_h = 11, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 178, .adv_w = 134, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 184, .adv_w = 134, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 187, .adv_w = 134, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 193, .adv_w = 134, .box_w = 5, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 200, .adv_w = 134, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 212, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 221, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 229, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 237, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 245, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 253, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 261, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 269, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 277, .adv_w = 134, .box_w = 5, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 284, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 292, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 300, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 308, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 316, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 324, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 332, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 340, .adv_w = 134, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 350, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 358, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 366, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 375, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 383, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 392, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 402, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 411, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 420, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 428, .adv_w = 134, .box_w = 3, .box_h = 14, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 434, .adv_w = 134, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 445, .adv_w = 134, .box_w = 3, .box_h = 14, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 451, .adv_w = 134, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 456, .adv_w = 134, .box_w = 7, .box_h = 1, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 457, .adv_w = 134, .box_w = 2, .box_h = 2, .ofs_x = 3, .ofs_y = 9},
    {.bitmap_index = 458, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 464, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 472, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 478, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 486, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 492, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 500, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 509, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 517, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 525, .adv_w = 134, .box_w = 5, .box_h = 13, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 534, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 542, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 551, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 558, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 564, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 570, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 579, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 588, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 594, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 600, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 608, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 614, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 620, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 627, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 633, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 642, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 648, .adv_w = 134, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 659, .adv_w = 134, .box_w = 1, .box_h = 14, .ofs_x = 4, .ofs_y = -2},
    {.bitmap_index = 661, .adv_w = 134, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 672, .adv_w = 134, .box_w = 6, .box_h = 3, .ofs_x = 1, .ofs_y = 4}
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
lv_font_t jetbrains_light_14 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 16,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0)
    .underline_position = -2,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if JETBRAINS_LIGHT_14*/

