
#include <drivers/vga/vga.h>




int cursor_x = 0;
int cursor_y = 0;

void init_cursor(){
	enable_cursor();
	update_cursor(0,0);
}

void enable_cursor()
{
	
}

void disable_cursor()
{
	outportb(0x3D4, 0x0A);
	outportb(0x3D5, 0x20);
}


void update_cursor(int x, int y)
{   
    
    putpixel(cursor_x,cursor_y++,0);
    putpixel(cursor_x,cursor_y++,0);
    putpixel(cursor_x,cursor_y++,0);
    putpixel(cursor_x,cursor_y++,0);
    putpixel(cursor_x,cursor_y++,0);
    putpixel(cursor_x,cursor_y++,0);
    putpixel(cursor_x,cursor_y++,0);
    putpixel(cursor_x,cursor_y++,0);

    //cursor_y += 9;
    cursor_x =x;
    cursor_y = y;
    putpixel(cursor_x,cursor_y++,5);
    putpixel(cursor_x,cursor_y++,5);
    putpixel(cursor_x,cursor_y++,5);
    putpixel(cursor_x,cursor_y++,5);
    putpixel(cursor_x,cursor_y++,5);
    putpixel(cursor_x,cursor_y++,5);
    putpixel(cursor_x,cursor_y++,5);
    putpixel(cursor_x,cursor_y++,5);
    
    cursor_x = x;
    cursor_y = y;
    
    

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