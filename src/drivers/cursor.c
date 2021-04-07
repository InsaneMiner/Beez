#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <kernel/system.h>

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

int cursor_x = 0;
int cursor_y = 0;

void init_cursor(){
	enable_cursor();
	update_cursor(0,0);
}

void enable_cursor()
{
	outportb(0x3D4, 0x0A);
	outportb(0x3D5, (inportb(0x3D5) & 0xC0) | 14);
	outportb(0x3D4, 0x0B);
	outportb(0x3D5, (inportb(0x3D5) & 0xE0) | 15);
}

void disable_cursor()
{
	outportb(0x3D4, 0x0A);
	outportb(0x3D5, 0x20);
}


void update_cursor(int x, int y)
{
    cursor_x = x;
    cursor_y = y;

	uint16_t pos = cursor_y * VGA_WIDTH + cursor_x;
 
	outportb(0x3D4, 0x0F);
	outportb(0x3D5, (uint8_t) (pos & 0xFF));
	outportb(0x3D4, 0x0E);
	outportb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}




uint16_t get_cursor_position(void)
{
    uint16_t pos = 0;
    outportb(0x3D4, 0x0F);
    pos |= inportb(0x3D5);
    outportb(0x3D4, 0x0E);
    pos |= ((uint16_t)inportb(0x3D5)) << 8;
    return pos;
}