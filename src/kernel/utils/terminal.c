// terminal.c
// Written by Harry Rigg
// Contains basic terminal functions

#include <kernel/utils/terminal.h>

// Prints a formatted string
void 
printk(char* text)
{
	vga_print(text);
}

void
knl()
{
	vga_putch('\n');
}
