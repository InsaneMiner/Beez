#pragma once
#include <stdint.h>



#ifndef VGA_H
#define VGA_H


void init_vga();
void clear_screen();
void clear_color(uint8_t color);
void putpixel(uint16_t x, uint16_t y, uint8_t color);
void draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t color);
void draw_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t color);
void fill_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t color);
void draw_circle(uint16_t x, uint16_t y, uint16_t radius, uint8_t color);
void draw_diamond(uint16_t x, uint16_t y, uint16_t radius, uint8_t color);

#endif


