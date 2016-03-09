// io.c
// Written by Harry Rigg
// General port input and output functions

#include <kernel/sys/io.h>

// Reads in byte from specified port
uint8_t 
inb(uint16_t port)
{
	uint8_t val;
	__asm__ __volatile__("inb %1, %0":"=a"(val):"dN"(port));
	return val;
}

// Sends a byte of data to specified port
void 
outb(uint16_t port, uint8_t data)
{
	__asm__ __volatile__("outb %1, %0":: "dN" (port), "a"(data));
}

// Reads in word from specified port
uint16_t 
inw(uint16_t port)
{
	uint16_t val;
	__asm__ __volatile__("inw %w1, %0":"=a"(val):"Nd"(port));
	return val;
}

// Sends a word of data to specified port
void 
outw(uint16_t port, uint16_t data)
{
	__asm__ __volatile__("outw %w0, %w1"::"a"(data), "Nd"(port));
}

