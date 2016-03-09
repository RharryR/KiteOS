// pit.c
// Written by Harry Rigg
// Driver for PIT (Programmable Interrupt Timer)

#include <kernel/drivers/timing/pit.h>

// Sleeps for the specified ticks
void 
sleep(size_t ticks)
{
	size_t wait = pit_clocks + ticks;
	while(pit_clocks != wait);
}

// Called on PIT interrupt
void 
pit_interrupt(registers_t* reg)
{ 
	pit_clocks++;
	outb(0x20, 0x20);
}

// Sets the PIT freq
void 
pit_freq(uint32_t freq)
{
	uint32_t div = 1193180 / freq;
	
	outb(0x43, 0x36);
	
	uint8_t l = (uint8_t) ( div & 0xFF );
	uint8_t h = (uint8_t) (( div >> 8) & 0xFF );
	
	outb(0x40, l);
	outb(0x40, h);
}

// Initiates the PIT
void 
pit_init()
{
	pit_clocks=0;
	install_irq(0, pit_interrupt);
}
