#include "lvgl/lvgl.h"

/*******************************************************************************
 * Size: 14 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifndef JETBRAINS_BOLD_14
#define JETBRAINS_BOLD_14 1
#endif

#if JETBRAINS_BOLD_14

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t gylph_bitmap[] = {
    /* U+20 " " */
    0x0,

    /* U+21 "!" */
    0xff, 0xfc, 0x30,

    /* U+22 "\"" */
    0xde, 0xf7, 0xb0,

    /* U+23 "#" */
    0x12, 0x14, 0x7f, 0x24, 0x24, 0x24, 0xfe, 0x2c,
    0x68, 0x48,

    /* U+24 "$" */
    0x10, 0x21, 0xf6, 0xbd, 0x1e, 0x1e, 0xf, 0x17,
    0xaf, 0xfb, 0xe1, 0x2, 0x0,

    /* U+25 "%" */
    0xf1, 0x92, 0x94, 0xf4, 0x8, 0x16, 0x29, 0x29,
    0x49, 0x86,

    /* U+26 "&" */
    0x79, 0x9b, 0x3, 0x6, 0x1e, 0xf7, 0x66, 0xcc,
    0xec,

    /* U+27 "'" */
    0xff,

    /* U+28 "(" */
    0x19, 0xd9, 0x8c, 0x63, 0x18, 0xc6, 0x38, 0xc3,
    0x84,

    /* U+29 ")" */
    0xc7, 0xc, 0x31, 0x8c, 0x63, 0x18, 0xce, 0x6e,
    0x40,

    /* U+2A "*" */
    0x18, 0x18, 0xdb, 0xff, 0x18, 0x3c, 0x66,

    /* U+2B "+" */
    0x30, 0x60, 0xc7, 0xf3, 0x6, 0xc, 0x0,

    /* U+2C "," */
    0x6d, 0x60,

    /* U+2D "-" */
    0xfc,

    /* U+2E "." */
    0xe0,

    /* U+2F "/" */
    0x6, 0x18, 0x30, 0x41, 0x83, 0x4, 0x18, 0x30,
    0xc1, 0x83, 0xc, 0x18, 0x0,

    /* U+30 "0" */
    0x7d, 0x8f, 0x1e, 0x3f, 0x78, 0xf1, 0xe3, 0xc6,
    0xf8,

    /* U+31 "1" */
    0x39, 0xf3, 0x60, 0xc1, 0x83, 0x6, 0xc, 0x19,
    0xfc,

    /* U+32 "2" */
    0x7b, 0x3c, 0xc3, 0x1c, 0x63, 0x9c, 0xe3, 0xf0,

    /* U+33 "3" */
    0xfc, 0x18, 0x61, 0xc3, 0xc0, 0xc1, 0xe3, 0xc6,
    0xf8,

    /* U+34 "4" */
    0x18, 0x63, 0x1c, 0x6f, 0x3c, 0xff, 0xc, 0x30,

    /* U+35 "5" */
    0xff, 0x83, 0x7, 0xec, 0x60, 0xc1, 0x83, 0xc6,
    0xf8,

    /* U+36 "6" */
    0x18, 0x60, 0xc3, 0x7, 0xd8, 0xf1, 0xe3, 0xc6,
    0x78,

    /* U+37 "7" */
    0xff, 0x8f, 0x10, 0x60, 0xc3, 0x6, 0x8, 0x30,
    0x60,

    /* U+38 "8" */
    0x7d, 0x8f, 0x1e, 0x33, 0x98, 0xf1, 0xe3, 0xc6,
    0xf8,

    /* U+39 "9" */
    0x79, 0x8f, 0x1e, 0x3c, 0x6f, 0x83, 0xc, 0x18,
    0x60,

    /* U+3A ":" */
    0xc0, 0x3,

    /* U+3B ";" */
    0x60, 0x0, 0x3, 0x6b, 0x0,

    /* U+3C "<" */
    0x2, 0x1c, 0xe7, 0xc, 0xe, 0x7, 0x3,

    /* U+3D "=" */
    0xfc, 0x0, 0x0, 0xfc,

    /* U+3E ">" */
    0x1, 0x81, 0xe0, 0xf0, 0x67, 0xbc, 0x60,

    /* U+3F "?" */
    0xf8, 0x30, 0xc3, 0x79, 0x86, 0x0, 0x1, 0x80,

    /* U+40 "@" */
    0x3c, 0x66, 0xc3, 0xdb, 0xf7, 0xf3, 0xf3, 0xf3,
    0xf3, 0xdf, 0xc0, 0x60, 0x38,

    /* U+41 "A" */
    0x18, 0x1c, 0x3c, 0x34, 0x34, 0x26, 0x7e, 0x62,
    0x63, 0x43,

    /* U+42 "B" */
    0xfd, 0x8f, 0x1e, 0x3f, 0x98, 0xf1, 0xe3, 0xc7,
    0xf8,

    /* U+43 "C" */
    0x7d, 0x8f, 0x1e, 0xc, 0x18, 0x30, 0x63, 0xc6,
    0xf8,

    /* U+44 "D" */
    0xf9, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc7,
    0xf0,

    /* U+45 "E" */
    0xff, 0xc, 0x30, 0xff, 0xc, 0x30, 0xc3, 0xf0,

    /* U+46 "F" */
    0xff, 0x83, 0x6, 0xf, 0xd8, 0x30, 0x60, 0xc1,
    0x80,

    /* U+47 "G" */
    0x7d, 0x8f, 0x1e, 0xc, 0x1b, 0xf1, 0xe3, 0xc6,
    0xf8,

    /* U+48 "H" */
    0xcf, 0x3c, 0xf3, 0xff, 0x3c, 0xf3, 0xcf, 0x30,

    /* U+49 "I" */
    0xfc, 0xc3, 0xc, 0x30, 0xc3, 0xc, 0x33, 0xf0,

    /* U+4A "J" */
    0x1e, 0xc, 0x18, 0x30, 0x60, 0xc1, 0xe3, 0xc6,
    0xf8,

    /* U+4B "K" */
    0xc7, 0x9b, 0x36, 0xcf, 0x9b, 0x33, 0x66, 0xc5,
    0x8c,

    /* U+4C "L" */
    0xc3, 0xc, 0x30, 0xc3, 0xc, 0x30, 0xc3, 0xf0,

    /* U+4D "M" */
    0xcf, 0xdf, 0xbf, 0x7e, 0xfa, 0xf1, 0xe3, 0xc7,
    0x8c,

    /* U+4E "N" */
    0xe7, 0xcf, 0x9f, 0xbd, 0x7a, 0xf7, 0xe7, 0xcf,
    0x9c,

    /* U+4F "O" */
    0x7b, 0x3c, 0xf3, 0xcf, 0x3c, 0xf3, 0xcd, 0xe0,

    /* U+50 "P" */
    0xfd, 0x8f, 0x1e, 0x3c, 0x7f, 0xb0, 0x60, 0xc1,
    0x80,

    /* U+51 "Q" */
    0x7d, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc6,
    0xf8, 0x30, 0x60, 0x60,

    /* U+52 "R" */
    0xfd, 0x8f, 0x1e, 0x3c, 0x7f, 0xb6, 0x66, 0xcd,
    0x8c,

    /* U+53 "S" */
    0x7d, 0x8f, 0x7, 0xf, 0xc7, 0xc3, 0x83, 0xc6,
    0xf8,

    /* U+54 "T" */
    0xfe, 0x30, 0x60, 0xc1, 0x83, 0x6, 0xc, 0x18,
    0x30,

    /* U+55 "U" */
    0xcf, 0x3c, 0xf3, 0xcf, 0x3c, 0xf3, 0xcd, 0xe0,

    /* U+56 "V" */
    0x43, 0x63, 0x62, 0x66, 0x26, 0x36, 0x34, 0x3c,
    0x1c, 0x18,

    /* U+57 "W" */
    0x9b, 0x9b, 0xda, 0xda, 0xda, 0xfa, 0xea, 0x6a,
    0x66, 0x66,

    /* U+58 "X" */
    0x63, 0x66, 0x34, 0x3c, 0x18, 0x1c, 0x3c, 0x36,
    0x66, 0x63,

    /* U+59 "Y" */
    0xc3, 0x66, 0x66, 0x34, 0x3c, 0x18, 0x18, 0x18,
    0x18, 0x18,

    /* U+5A "Z" */
    0xfc, 0x31, 0x86, 0x30, 0xc6, 0x18, 0xc3, 0xf0,

    /* U+5B "[" */
    0xfc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xf0,

    /* U+5C "\\" */
    0xc1, 0x81, 0x3, 0x6, 0x4, 0xc, 0x18, 0x18,
    0x30, 0x60, 0x60, 0xc0, 0x80,

    /* U+5D "]" */
    0xf3, 0x33, 0x33, 0x33, 0x33, 0x33, 0xf0,

    /* U+5E "^" */
    0x30, 0xc7, 0x9a, 0x4f, 0x10,

    /* U+5F "_" */
    0xfe,

    /* U+60 "`" */
    0x60,

    /* U+61 "a" */
    0x3c, 0xcc, 0x1b, 0xfc, 0x78, 0xf1, 0xbf,

    /* U+62 "b" */
    0xc3, 0xf, 0xb3, 0xcf, 0x3c, 0xf3, 0xcf, 0xe0,

    /* U+63 "c" */
    0x79, 0x9b, 0x16, 0xc, 0x18, 0xf3, 0x3c,

    /* U+64 "d" */
    0xc, 0x37, 0xf3, 0xcf, 0x3c, 0xf3, 0xcd, 0xf0,

    /* U+65 "e" */
    0x7d, 0x8f, 0x1f, 0xfc, 0x18, 0x31, 0xbe,

    /* U+66 "f" */
    0x1e, 0x63, 0xf9, 0x83, 0x6, 0xc, 0x18, 0x30,
    0x60,

    /* U+67 "g" */
    0x7f, 0x3c, 0xf3, 0xcf, 0x3c, 0xdf, 0xc, 0x37,
    0x80,

    /* U+68 "h" */
    0xc3, 0xf, 0xb3, 0xcf, 0x3c, 0xf3, 0xcf, 0x30,

    /* U+69 "i" */
    0x0, 0x60, 0x7, 0x83, 0x6, 0xc, 0x18, 0x30,
    0x63, 0xf8,

    /* U+6A "j" */
    0x0, 0xc1, 0xf1, 0x8c, 0x63, 0x18, 0xc6, 0x31,
    0xf8,

    /* U+6B "k" */
    0xc1, 0x83, 0x1e, 0x6d, 0x9f, 0x36, 0x66, 0xcd,
    0x8c,

    /* U+6C "l" */
    0xf8, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
    0x18, 0xf,

    /* U+6D "m" */
    0xfd, 0xef, 0xdf, 0xbf, 0x7e, 0xfd, 0xfb,

    /* U+6E "n" */
    0xfb, 0x3c, 0xf3, 0xcf, 0x3c, 0xf3,

    /* U+6F "o" */
    0x7b, 0x3c, 0xf3, 0xcf, 0x3c, 0xde,

    /* U+70 "p" */
    0xfb, 0x3c, 0xf3, 0xcf, 0x3c, 0xfe, 0xc3, 0xc,
    0x0,

    /* U+71 "q" */
    0x7f, 0x3c, 0xf3, 0xcf, 0x3c, 0xdf, 0xc, 0x30,
    0xc0,

    /* U+72 "r" */
    0xfd, 0x8f, 0x1e, 0xc, 0x18, 0x30, 0x60,

    /* U+73 "s" */
    0x7d, 0x8f, 0x7, 0xe7, 0xe0, 0xf1, 0xbe,

    /* U+74 "t" */
    0x30, 0x63, 0xf9, 0x83, 0x6, 0xc, 0x18, 0x30,
    0x3c,

    /* U+75 "u" */
    0xcf, 0x3c, 0xf3, 0xcf, 0x3c, 0xde,

    /* U+76 "v" */
    0xc7, 0x8b, 0x32, 0x66, 0x8f, 0xe, 0x18,

    /* U+77 "w" */
    0xd9, 0xdb, 0x5b, 0x5b, 0x56, 0x56, 0x66, 0x66,

    /* U+78 "x" */
    0xcc, 0xd9, 0xe1, 0x83, 0x8f, 0x33, 0x63,

    /* U+79 "y" */
    0xc7, 0x8b, 0x33, 0x66, 0x87, 0xe, 0x18, 0x30,
    0x60, 0x80,

    /* U+7A "z" */
    0xfc, 0x31, 0x8c, 0x31, 0x8c, 0x3f,

    /* U+7B "{" */
    0xe, 0x30, 0x60, 0xc1, 0x83, 0x38, 0xc, 0x18,
    0x30, 0x60, 0xc0, 0xe0,

    /* U+7C "|" */
    0xff, 0xff, 0xff, 0xc0,

    /* U+7D "}" */
    0xe0, 0x60, 0xc1, 0x83, 0x6, 0x3, 0x98, 0x30,
    0x60, 0xc1, 0x8e, 0x0,

    /* U+7E "~" */
    0xe7, 0xaf, 0x38
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 134, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 134, .box_w = 2, .box_h = 10, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 134, .box_w = 5, .box_h = 4, .ofs_x = 2, .ofs_y = 6},
    {.bitmap_index = 7, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 17, .adv_w = 134, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 30, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 40, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 49, .adv_w = 134, .box_w = 2, .box_h = 4, .ofs_x = 3, .ofs_y = 6},
    {.bitmap_index = 50, .adv_w = 134, .box_w = 5, .box_h = 14, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 59, .adv_w = 134, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 68, .adv_w = 134, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 75, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 82, .adv_w = 134, .box_w = 3, .box_h = 4, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 84, .adv_w = 134, .box_w = 6, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 85, .adv_w = 134, .box_w = 3, .box_h = 1, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 86, .adv_w = 134, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 99, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 108, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 117, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 125, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 134, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 142, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 151, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 160, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 169, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 178, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 187, .adv_w = 134, .box_w = 2, .box_h = 8, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 189, .adv_w = 134, .box_w = 3, .box_h = 11, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 194, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 201, .adv_w = 134, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 205, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 212, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 220, .adv_w = 134, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 233, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 243, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 252, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 261, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 270, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 278, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 287, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 296, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 304, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 312, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 321, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 330, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 338, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 347, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 356, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 364, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 373, .adv_w = 134, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 385, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 394, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 403, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 412, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 420, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 430, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 440, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 450, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 460, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 468, .adv_w = 134, .box_w = 4, .box_h = 13, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 475, .adv_w = 134, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 488, .adv_w = 134, .box_w = 4, .box_h = 13, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 495, .adv_w = 134, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 500, .adv_w = 134, .box_w = 7, .box_h = 1, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 501, .adv_w = 134, .box_w = 4, .box_h = 1, .ofs_x = 2, .ofs_y = 10},
    {.bitmap_index = 502, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 509, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 517, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 524, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 532, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 539, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 548, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 557, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 565, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 575, .adv_w = 134, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 584, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 593, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 603, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 610, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 616, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 622, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 631, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 640, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 647, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 654, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 663, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 669, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 676, .adv_w = 134, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 684, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 691, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 701, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 707, .adv_w = 134, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 719, .adv_w = 134, .box_w = 2, .box_h = 13, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 723, .adv_w = 134, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 735, .adv_w = 134, .box_w = 7, .box_h = 3, .ofs_x = 1, .ofs_y = 4}
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
lv_font_t jetbrains_bold_14 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 15,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0)
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if JETBRAINS_BOLD_14*/

