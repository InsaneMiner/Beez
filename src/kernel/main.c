#include <stdbool.h>

#include <kernel/console.h>
#include <kernel/GDT.h>
#include <kernel/IDT.h>
#include <kernel/ISR.h>
#include <kernel/IRQ.h>
#include <kernel/timer.h>
#include <kernel/paging.h>
#include <kernel/speaker.h>



#include <drivers/kb.h>


#include <libs/itoa.h>
#include <libs/stdclib.h> 


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
	// enables interrupts. really needed.
	__asm__ __volatile__("sti"); 

	
}



void main(){
	init_system();
	
  	//terminal_setcolor(9);
 
  	prints("Welcome to Beez Kernel\b\n");
	//timer_wait(100);
	//prints("Yo done");

	/*
	while (1){
		beep(1000,10);
		beep(1000,10);
		beep(1000,10);
		beep(500,10);
		beep(500,10);
		beep(200,10);
		beep(200,10);
	}
	*/
	prints(">> ");
	kb_input();

	
  	//Makes sure that the system does not just reboot everytime its done.
  	for (;;);
}

