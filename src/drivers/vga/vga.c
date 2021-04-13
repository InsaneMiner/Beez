#include <drivers/vga/vga.h>
#include <kernel/system.h>

/*
See Intel® OpenSource HD Graphics PRM pdf file
for following defined data for each vga register
and its explaination
*/
static uint8_t seq_data[5] = {0x03, 0x01, 0x0F, 0x00, 0x0E};
static uint8_t crtc_data[25] = {0x5F, 0x4F, 0x50, 0x82, 
                              0x54, 0x80, 0xBF, 0x1F,
                              0x00, 0x41, 0x00, 0x00, 
                              0x00, 0x00, 0x00, 0x00,
                              0x9C, 0x0E, 0x8F, 0x28,	
                              0x40, 0x96, 0xB9, 0xA3,
                              0xFF};

static uint8_t gc_data[9] = {0x00, 0x00, 0x00, 0x00, 
                          0x00, 0x40, 0x05, 0x0F,
                          0xFF};

static uint8_t ac_data[21] = {0x00, 0x01, 0x02, 0x03,
                            0x04, 0x05, 0x06, 0x07,
                            0x08, 0x09, 0x0A, 0x0B,
                            0x0C, 0x0D, 0x0E, 0x0F,
                            0x41, 0x00, 0x0F, 0x00,
                            0x00};
#define VGA_ADDRESS 0xA0000
#define VGA_MAX 0xF9FF
#define VGA_MAX_WIDTH 320
#define VGA_MAX_HEIGHT 200

uint8_t* vga_buffer;

enum vga_color {
  BLACK,
  BLUE,
  GREEN,
  CYAN,
  RED,
  MAGENTA,
  BROWN,
  GREY,
  DARK_GREY,
  BRIGHT_BLUE,
  BRIGHT_GREEN,
  BRIGHT_CYAN,
  BRIGHT_RED,
  BRIGHT_MAGENTA,
  YELLOW,
  WHITE,
};

/* Attribute Controller Registers */
#define	VGA_AC_INDEX 0x3C0
#define	VGA_AC_READ 0x3C1
#define	VGA_AC_WRITE 0x3C0

/*
Miscellaneous Output
*/
#define	VGA_MISC_READ 0x3CC
#define	VGA_MISC_WRITE 0x3C2

/* Sequencer Registers */
#define VGA_SEQ_INDEX 0x3C4
#define VGA_SEQ_DATA 0x3C5

/* VGA Color Palette Registers */
#define	VGA_DAC_READ_INDEX 0x3C7
#define	VGA_DAC_WRITE_INDEX 0x3C8
#define	VGA_DAC_DATA 0x3C9

/* Graphics Controller Registers */
#define VGA_GC_INDEX 0x3CE
#define VGA_GC_DATA 0x3CF

/* CRT Controller Registers */
#define VGA_CRTC_INDEX 0x3D4
#define VGA_CRTC_DATA 0x3D5

/* General Control and Status Registers */
#define	VGA_INSTAT_READ 0x3DA


void set_misc()
{
  outportb(VGA_MISC_WRITE, 0x63);
}

void set_seq()
{
  // write sequence data to index of 0-4
  for(uint8_t index = 0; index < 5; index++){
    // first set index
    outportb(VGA_SEQ_INDEX, index);
    // write data at that index
    outportb(VGA_SEQ_DATA, seq_data[index]);
  }
}

void set_crtc()
{
  // write crtc data to index of 0-24
  for(uint8_t index = 0; index < 25; index++){
    outportb(VGA_CRTC_INDEX, index);
	  outportb(VGA_CRTC_DATA, crtc_data[index]);
  }
}

void set_gc()
{
  // write gc data to index of 0-8
  for(uint8_t index = 0; index < 9; index++){
    outportb(VGA_GC_INDEX, index);
    outportb(VGA_GC_DATA, gc_data[index]);
  }
}

void set_ac()
{
  uint8_t d;
  // write ac data to index of 0-20
  for(uint8_t index = 0; index < 21; index++){
    outportb(VGA_AC_INDEX, index);
    outportb(VGA_AC_WRITE, ac_data[index]);
  }
  d = inportb(VGA_INSTAT_READ);
  outportb(VGA_AC_INDEX, d | 0x20);
}

void clear_screen()
{
  for(uint32_t index = 0; index < VGA_MAX; index++)
    vga_buffer[index] = 0;
}

void clear_color(uint8_t color)
{
  for(uint32_t index = 0; index < VGA_MAX; index++)
    vga_buffer[index] = color;
}

void init_vga()
{
  set_misc();
  set_seq();
  set_crtc();
  set_gc();
  set_ac();

  vga_buffer = (uint8_t*)VGA_ADDRESS;

  clear_screen();
}

void putpixel(uint16_t x, uint16_t y, uint8_t color)
{
  uint32_t index = 0;
  index = 320 * y + x;
  if(index < VGA_MAX)
    vga_buffer[index] = color;
}

void draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t color)
{
  if(y1 == y2){
    for(uint16_t i = x1; i <= x2; i++)
      putpixel(i, y1, color);
    return;
  }

  if(x1 == x2){
    for(uint16_t i = y1; i <= y2; i++){
      putpixel(x1, i, color);
    }
    return;
  }
}

void draw_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t color)
{
  draw_line(x, y, x, y + height, color);
  draw_line(x, y, x + width, y, color);
  draw_line(x + width, y, x + width, y + height, color);
  draw_line(x, y + height, x + width, y + height, color);
}

void fill_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t color)
{
  draw_line(x, y, x, y + height, color);
  draw_line(x, y, x + width, y, color);
  draw_line(x + width, y, x + width, y + height, color);
  draw_line(x, y + height, x + width, y + height, color);
  for(int i = y; i < y + height; i++){
    draw_line(x, i, x + width, i, color);
  }
}

void draw_bresenham_circle(int xc, int yc, int x, int y, uint8_t color) 
{ 
  putpixel(xc+x, yc+y, color); 
  putpixel(xc-x, yc+y, color); 
  putpixel(xc+x, yc-y, color); 
  putpixel(xc-x, yc-y, color); 
  putpixel(xc+y, yc+x, color); 
  putpixel(xc-y, yc+x, color); 
  putpixel(xc+y, yc-x, color); 
  putpixel(xc-y, yc-x, color); 
} 

void draw_circle(uint16_t x, uint16_t y, uint16_t radius, uint8_t color)
{
  int x2 = 0, y2 = radius;
  int d = 3 - 2 * radius;
  draw_bresenham_circle(x, y, x2, y2, color);
  while(y2 >= x2){
    x2++;
    if(d > 0){
      y2--;
      d = d + 4 * (x2 - y2) + 10;
    }else{
      d = d + 4 * x2 + 6;
    } 
    draw_bresenham_circle(x, y, x2, y2, color);
  } 
}

void draw_diamond(uint16_t x, uint16_t y, uint16_t radius, uint8_t color)
{
  uint16_t x2 = 0, y2 = radius;
  uint16_t d = 3 - 2 * radius;
  draw_bresenham_circle(x, y, x2, y2, color);
  while(y2 >= x2){
    x2++;
    if(d > 0){
      y2--;
      d = d + 4 * (x2 - y2) + 10;
    }else{
      d = d + 4 * x2 + 6;
    } 
    draw_bresenham_circle(x, y, x2, y2, color);
  } 
}

