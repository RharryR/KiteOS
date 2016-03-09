// rtc.c
// Written by Harry Rigg
// Driver for RTC (Real Time Clock) and CMOS

#include <kernel/drivers/timing/rtc.h>

// Called on RTC interrupt
void 
rtc_interrupt(registers_t* reg)
{
	outb(0xA0, 0x20);
	outb(0x20, 0x20);
}

// Initiates the IRQ and tells it to interrupt
void 
rtc_init()
{
	install_irq(8, rtc_interrupt);
	
	__asm__ __volatile__ ("cli");
	
	outb(0x70, 0x8B);
	char foo = inb(0x71);
	outb(0x70, 0x8B);
	outb(0x71, foo | 0x40);
	
	__asm__ __volatile__ ("sti");
} 
