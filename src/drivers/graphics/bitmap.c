#include <drivers/graphics/bitmap.h>
#include <drivers/vga/vga.h>
#include <drivers/graphics/font.h>
#include <stdint.h>



// 0 = no-pixel, 1 = pixel





// putpixels of A-Z bits from right-to-left
void draw_alpha_bitmaps(uint16_t index, uint16_t x, uint16_t y, uint8_t color)
{
  uint16_t temp = 0, pix = 0;
  int one = 1;
  for(uint8_t i = 0; i < BITMAP_SIZE; i++){
    temp = x;
    x += BITMAP_SIZE;
    pix = font[index][i];
    while(one == 1){
      if (pix & 1){
        putpixel(x, y, color);
      }
      else{
        putpixel(x,y,0);
      }
      
      
      pix >>= 1;
      x--;  
      if (temp == x){
        break;
      }
    }
    x = temp;
    y++;
  }
}

void draw_char(uint16_t x, uint16_t y, uint8_t color, char ch)
{
  //draw_string(x,y,2,(int)ch);
  draw_alpha_bitmaps((int)ch,  x, y, color);
}

void draw_string(uint16_t x, uint16_t y, uint8_t color, char *str)
{
  uint32_t index = 0;

  while(str[index]){
    draw_char(x, y, color, str[index]);
    x += BITMAP_SIZE + 1;
    index++;
  }
}

