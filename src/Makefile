HOME := $(shell echo "$$HOME")


INCLUDES=./includes

CC=$(HOME)/opt/cross/bin/i686-elf-gcc
AS=$(HOME)/opt/cross/bin/i686-elf-as
CC_OPTIONS=-w -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I $(INCLUDES)
AS_OPTIONS=-f elf32 -I./includes/assembly
qemu-options=-soundhw pcspk
NASM=nasm
OBJ = kernel/kernel.o \


compile-kernel:
	$(CC) -c kernel/main.c -o ./kernel.o $(CC_OPTIONS)
	$(CC) -c kernel/console.c -o ./console.o $(CC_OPTIONS)
	$(CC) -c drivers/kb.c -o ./kb.o $(CC_OPTIONS)
	$(CC) -c kernel/system.c -o ./system.o $(CC_OPTIONS)
	$(CC) -c libs/string.c -o ./string.lib.o $(CC_OPTIONS)
	$(CC) -c drivers/cursor.c -o ./cursor.driver.o $(CC_OPTIONS)
	$(CC) -c kernel/GDT.c -o ./GDT.o $(CC_OPTIONS)
	$(CC) -c libs/itoa.c -o ./itoa.lib.o $(CC_OPTIONS)
	$(CC) -c kernel/IDT.c -o ./IDT.o $(CC_OPTIONS)
	$(CC) -c kernel/ISR.c -o ./ISR.o $(CC_OPTIONS)
	$(CC) -c kernel/IRQ.c -o ./IRQ.o $(CC_OPTIONS)
	$(CC) -c libs/kheap.c -o ./kheap.libs.o $(CC_OPTIONS)
	$(CC) -c kernel/timer.c -o ./timer.o $(CC_OPTIONS)
	$(CC) -c kernel/paging.c -o ./paging.o $(CC_OPTIONS)
	$(CC) -c libs/ordered_array.c -o ./ordered_array.o $(CC_OPTIONS)
	$(CC) -c kernel/speaker.c -o ./speaker.o $(CC_OPTIONS)
	$(NASM) $(AS_OPTIONS) boot/boot.s -o ./boot.o 
	$(CC) -T boot/linker.ld -o Beez.bin -ffreestanding -O2 -nostdlib ./boot.o ./kernel.o ./console.o ./kb.o ./system.o ./string.lib.o ./cursor.driver.o ./itoa.lib.o ./GDT.o ./IDT.o ./ISR.o ./IRQ.o ./timer.o ./kheap.libs.o ./paging.o ./ordered_array.o ./speaker.o -lgcc
	rm *.o

iso: compile-kernel
	mkdir -p isodir/boot/grub
	cp Beez.bin isodir/boot/Beez.bin
	cp GRUB2/grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o Beez.iso isodir
	rm -rf isodir

clean:
	rm -f *.o *.iso *.bin

qemu-kernel: compile-kernel
	qemu-system-i386 -kernel Beez.bin $(qemu-options)

qemu-iso: iso
	qemu-system-i386 -cdrom Beez.iso $(qemu-options)
qemu: iso
	qemu-system-i386 -cdrom Beez.iso $(qemu-options)
