#ifndef BITMAP_H
#define BITMAP_H

#include <stdint.h>

#define BITMAP_SIZE 8

void draw_char(uint16_t x, uint16_t y, uint8_t color, char ch);
void draw_string(uint16_t x, uint16_t y, uint8_t color, char *str);

#endif
