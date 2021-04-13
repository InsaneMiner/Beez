#pragma once
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>




void enable_cursor();
void disable_cursor();
void init_cursor();
void update_cursor(int x, int y);
uint16_t get_cursor_position(void);