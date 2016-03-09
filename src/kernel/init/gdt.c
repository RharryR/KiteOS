// gdt.c
// Written by Harry Rigg
// Installs the GDT

#include <kernel/init/gdt.h>

// Installs a GDT entry
void 
install_gdt(int32_t index, size_t base, size_t limit, uint8_t access, uint8_t gran)
{
	gdt[index].base_low = (base & 0xFFFF);
	gdt[index].base_middle = (base >> 16) & 0xFF;
	gdt[index].base_high = (base >> 24) & 0xFF;
	
	gdt[index].limit_low = (limit & 0xFFFF);
	gdt[index].granularity = ((limit >> 16) & 0x0F);
	
	gdt[index].granularity |= (gran & 0xF0);
	gdt[index].access = access;
}

extern void place_gdt();

// Installs the GDT
void 
gdt_init()
{
	g_pointer.limit = (sizeof(struct gdt_entry) * 3) -1;
	g_pointer.base = &gdt;
	install_gdt(0,0,0,0,0);
	install_gdt(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
	install_gdt(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
	place_gdt();
}
