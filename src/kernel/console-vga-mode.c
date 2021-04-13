#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <libs/itoa.h>
#include <libs/stdclib.h>
#include <drivers/cursor.h>
#include <drivers/vga/vga.h>

#include <drivers/graphics/bitmap.h>
/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif
 

char * console_text = "";


/* Hardware text mode color constants. */
enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};
// Scrolls the text on the screen up by one line.

size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}
 
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
 
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;
 
void terminal_initialize(void) 
{
    terminal_column=0;
    terminal_row=0;
    terminal_color=2;
    init_vga();
    init_cursor();
}

//This scrolls the screen
/*
static void scroll()
{
   
   if(terminal_row >= 25)
   {
       int i;
       for (i = 0*80; i < 24*80; i++)
       {
           console_text[i] = console_text[i+80];
       }
       for (i = 24*80; i < 25*80; i++)
       {
           putch(' ');
       }
       terminal_column = 0;
       terminal_row = 24;
       update_cursor(terminal_column,terminal_row);
   }
   
} 
*/
void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}
 
 
void putch(char c) 
{   if (c == '\n'){
        terminal_row += 10;
        terminal_column=0;
    }

    else if (c == '\b'){
        if (terminal_column == 0 && terminal_row == 0){
            
        }
        else if (terminal_column == 0){
            terminal_row -= 10;
            terminal_column = 320 - BITMAP_SIZE + 1;
            
        }
        else{
            terminal_column -= BITMAP_SIZE + 1;
            putch(' ');
            terminal_column -= BITMAP_SIZE + 1;
        }
        
    }
	else if (c == '\t'){
		for (int x=0; x!=4; x++){
			putch(' ');
		}
	}
	else if (c == '\r'){
		terminal_column=0;
	}

    else{
        if (terminal_column >= 318){
            terminal_row +=10;
            terminal_column=0;
        }
        else if( terminal_column+BITMAP_SIZE+1 >= 320 ){
            terminal_row +=10;
            terminal_column=0;
        }
        draw_char(terminal_column,terminal_row,terminal_color,c);
        terminal_column += BITMAP_SIZE + 1;
    }
	//scroll();
    update_cursor(terminal_column,terminal_row);
}
 
void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		putch(data[i]);
}
 
void prints(const char* data) 
{
	terminal_write(data, strlen(data));
    
}



void printh(uint32_t n)
{
    uint32_t tmp;

    prints("0x");

    char noZeroes = 1;

    int i;
    for (i = 28; i > 0; i -= 4)
    {
        tmp = (n >> i) & 0xF;
        if (tmp == 0 && noZeroes != 0)
        {
            continue;
        }
    
        if (tmp >= 0xA)
        {
            noZeroes = 0;
            putch (tmp-0xA+'a' );
        }
        else
        {
            noZeroes = 0;
            putch( tmp+'0' );
        }
    }
  
    tmp = n & 0xF;
    if (tmp >= 0xA)
    {
        putch (tmp-0xA+'a');
    }
    else
    {
        putch (tmp+'0');
    }

}



void printi(int num)
{
  char str_num[digit_count(num)+1];
  itoa(num, str_num,10);
  prints(str_num);
}

void printb(uint32_t num)
{
  char bin_arr[32];
  uint32_t index = 31;
  uint32_t i;
  while (num > 0){
    if(num & 1){
      bin_arr[index] = '1';
    }else{
      bin_arr[index] = '0';
    }
    index--;
    num >>= 1;
  }

  for(i = 0; i < 32; ++i){
   if(i <= index)
      putch('0');
   else
     putch(bin_arr[i]);
  }
}
