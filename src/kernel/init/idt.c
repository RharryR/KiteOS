// idt.c
// Written by Harry Rigg
// Manages the IDT

#include <kernel/init/idt.h>

void 
install_idt(uint8_t index, size_t base, uint16_t sel, uint8_t flags)
{
	idt[index].base_lo = (base & 0xFFFF);
	idt[index].base_hi = (base >> 16) & 0xFFFF;
	
	idt[index].sel = sel;
	idt[index].always0 = 0;
	idt[index].flags = flags;
}

extern void place_idt();

void 
idt_init()
{
	i_pointer.limit = (sizeof(struct idt_entry) * 256)-1;
	i_pointer.base = &idt;
	memset(&idt, 0, sizeof(struct idt_entry) * 256);
	place_idt();
}
