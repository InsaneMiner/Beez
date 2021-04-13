#pragma once
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#define ushort unsigned short


#define ASSERT(b) ((b) ? (void)0 : panic_assert(__FILE__, __LINE__, #b))


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







static inline void breakpoint(void);

static inline void insb(int port, void *addr, int cnt);

static inline uint16_t inw(int port);

static inline void insw(int port, void *addr, int cnt);

static inline uint32_t inl(int port);

static inline void insl(int port, void *addr, int cnt);

static inline void outsb(int port, const void *addr, int cnt);

static inline void outw(int port, uint16_t data);

static inline void outsw(int port, const void *addr, int cnt);

static inline void outsl(int port, const void *addr, int cnt);

static inline void outl(int port, uint32_t data);

static inline void invlpg(void *addr);

static inline void lidt(void *p);

static inline void lgdt(void *p);

static inline void lldt(uint16_t sel);

static inline void ltr(uint16_t sel);

static inline void lcr0(uint32_t val);

static inline uint32_t rcr0(void);

static inline uint32_t rcr2(void);

static inline void lcr3(uint32_t val);

static inline uint32_t rcr3(void);

static inline void lcr4(uint32_t val);

static inline uint32_t rcr4(void);

static inline void tlbflush(void);

static inline uint32_t read_eflags(void);

static inline void write_eflags(uint32_t eflags); 

static inline uint32_t read_ebp(void);

static inline uint32_t read_esp(void);

static inline void cpuid(uint32_t info, uint32_t *eaxp, uint32_t *ebxp, uint32_t *ecxp, uint32_t *edxp);

static inline uint64_t read_tsc(void);

static inline uint32_t xchg(volatile uint32_t *addr, uint32_t newval);