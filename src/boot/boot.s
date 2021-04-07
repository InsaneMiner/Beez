bits 32
section .text
        align 4
        dd 0x1BADB002           
        dd 0x00                  
        dd - (0x1BADB002 + 0x00) 

global start
extern main	        

%include "kernel/GDT.S"
%include "kernel/IDT.S"
%include "kernel/ISR.S"
%include "kernel/IRQ.S"

start:
  cli 			
  mov esp, stack_space	
  call main
  hlt		 	

section .bss
resb 8192		
stack_space: