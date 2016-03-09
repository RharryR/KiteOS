// irq.c
// Written by Harry Rigg
// Utilities to install irq handlers on the PIC

#include <kernel/init/irq.h>

// Located in pmode.asm
extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

// Array of IRQ handlers
void
*irq_handlers[16]=
{
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0
};

// Installs a IRQ handler at the specified location
void 
install_irq(uint32_t loc, void (*handler)(registers_t* reg))
{
	irq_handlers[loc]=handler;
}

// Uninstalls a IRQ handler at the specified location
void 
uninstall_irq(uint32_t loc)
{
	irq_handlers[loc]=0;
}

// Remaps PIC
void 
remap()
{
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);
}

void 
irq_init()
{
	remap();
	install_idt(32, (uint32_t)irq0, 0x08, 0x8E);
	install_idt(33, (uint32_t)irq1, 0x08, 0x8E);
	install_idt(34, (uint32_t)irq2, 0x08, 0x8E);
	install_idt(35, (uint32_t)irq3, 0x08, 0x8E);
	install_idt(36, (uint32_t)irq4, 0x08, 0x8E);
	install_idt(37, (uint32_t)irq5, 0x08, 0x8E);
	install_idt(38, (uint32_t)irq6, 0x08, 0x8E);
	install_idt(39, (uint32_t)irq7, 0x08, 0x8E);
	install_idt(40, (uint32_t)irq8, 0x08, 0x8E);
	install_idt(41, (uint32_t)irq9, 0x08, 0x8E);
	install_idt(42, (uint32_t)irq10, 0x08, 0x8E);
	install_idt(43, (uint32_t)irq11, 0x08, 0x8E);
	install_idt(44, (uint32_t)irq12, 0x08, 0x8E);
	install_idt(45, (uint32_t)irq13, 0x08, 0x8E);
	install_idt(46, (uint32_t)irq14, 0x08, 0x8E);
	install_idt(47, (uint32_t)irq15, 0x08, 0x8E);
}

void 
irq_interrupted(registers_t* reg)
{
	void(*handler)(registers_t* reg);
	handler = irq_handlers[reg->interrupt_id - 32];
	if(handler)
	{
		handler(reg);
	}
	
	if(reg->interrupt_id >= 40)
	{
		outb(0x0A, 0x20);
	}
	outb(0x20, 0x20);
}
