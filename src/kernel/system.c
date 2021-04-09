#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <kernel/console.h>
#include <libs/itoa.h>


uint8_t inportb (uint16_t _port)
{
    	uint8_t rv;
    	__asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    	return rv;
}

void outportb (uint16_t _port, uint8_t _data)
{
	__asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}


void panic(char *msg){
	asm volatile("cli"); // disable interrupts. The system has crashed at this point so there is no point interrupts.
	prints(msg);
	for(;;); // halts by doing a infinite loop. This is like assemblies hlt, i think
}


extern void panic_assert(const char *file, uint32_t line, const char *desc)
{
    // An assertion failed, and we have to panic.
    asm volatile("cli"); // Disable interrupts.
    char buf[33];
    prints("ASSERTION-FAILED(");
    prints(desc);
    prints(") at ");
    prints(file);
    prints(":");
    prints(itoa(line,buf,10));
    putch('\n');
    // Halt by going into an infinite loop.
    for(;;);
}