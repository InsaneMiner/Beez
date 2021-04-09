#include <kernel/IRQ.h>
#include <kernel/system.h>
#include <kernel/console.h>
#include <libs/itoa.h>

#include <stdint.h>

uint32_t tick = 0;

static void timer_callback(struct regs *regs)
{
   tick++;
   //char buf[33];
   //char buf[33];
   //prints(itoa(tick,buf,10));
   //prints(" | ");
   //prints(itoa(tick,buf,10));
   //prints("\n");

    /* Every 18 clocks (approximately 1 second), we will
    *  display a message on the screen */
    if (tick % 18 == 0)
    {
        //prints("One second has passed\n");
    }
}

void init_timer(uint32_t frequency)
{

   irq_install_handler(0, &timer_callback);

   uint32_t divisor = 1193180 / frequency;


   outportb(0x43, 0x36);


   uint8_t l = (uint8_t)(divisor & 0xFF);
   uint8_t h = (uint8_t)( (divisor>>8) & 0xFF );


   outportb(0x40, l);
   outportb(0x40, h);
} 


void timer_wait(int ticks)
{
   unsigned long eticks;
   eticks = tick + ticks;
   // For some reason when it does not print something it does not work. if you know how to fix please do.
   while(tick < eticks){
         prints(" \b");
   }
}