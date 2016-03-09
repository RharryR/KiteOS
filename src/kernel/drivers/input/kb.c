// kb.c
// Written by Harry Rigg
// PS2 Keyboard driver

#include <kernel/drivers/input/kb.h>

// Called when a key is pressed
void 
kb_interrupt(registers_t* reg)
{
	uint8_t code = inb(0x60);
	if(code & 0x80)
	{
	}
	else
	{
		kb_buffer[kb_count] = code;
		kb_count++;
	}
	outb(0x20, 0x20);
}

// Initiates driver
void 
kb_init()
{
	install_irq(1, kb_interrupt);
}
