#include <stdbool.h>

#include <kernel/console.h>
#include <kernel/GDT.h>
#include <kernel/IDT.h>
#include <kernel/ISR.h>
#include <kernel/IRQ.h>
#include <kernel/timer.h>
#include <kernel/paging.h>
#include <kernel/speaker.h>

#include <driver/kb.h>
#include <libs/itoa.h>



// This function initializes the system
void init_system(){
	// Needed for makeing terminal work.
	terminal_initialize();
	// Needed for GDT(Global Descriptor Table)
	gdt_install();
	//Needed for IDT
	idt_install();
	//Needed for IRS(Interrupt Service Routines)
	isr_install();
	//Needed for IRQ

	
	irq_install();
	//Needed for timer
	
	init_timer(100);

	//This is for paging
	initialise_paging();

	__asm__ __volatile__("sti"); // enables interrupts. really needed.
	

}



void main(){
	init_system();

  	//terminal_setcolor(9);
 
  	prints("Welcome to Beez Kernel\n");
	timer_wait(100);
	prints("Yo done");
	

	
  	//Makes sure that the system does not just reboot everytime its done.
  	for (;;);
}

