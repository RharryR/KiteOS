// isr.c
// Written by Harry Rigg
// Installs exeception handlers on the system

#include <kernel/init/isr.h>

// Located in pmode.asm
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

// Exception messages
char *exception_messages[] = 
{
"Division By Zero",
"Debug",
"No Maskable Interrupt",
"Breakpoint",
"Into Detected Overflow",
"Out Of Bounds",
"Invalid Opcode",
"No Coprocessor",
"Double Fault",
"Coprocessor Segment Overrun",
"Bad TSS",
"Segment Not Present",
"Stack Fault",
"General Protection Fault",
"Page Fault",
"Unknown Interrupt",
"Coprocessor Fault",
"Alignment Check",
"Machine Check",
"Reserved",
"Reserved",
"Reserved",
"Reserved",
"Reserved",
"Reserved",
"Reserved",
"Reserved",
"Reserved",
"Reserved",
"Reserved",
"Reserved",
"Reserved"
};

// Installs exception handlers
void 
isr_init()
{
	install_idt(0, (uint32_t)isr0, 0x08, 0x8E);
	install_idt(1, (uint32_t)isr1, 0x08, 0x8E);
	install_idt(2, (uint32_t)isr2, 0x08, 0x8E);
	install_idt(3, (uint32_t)isr3, 0x08, 0x8E);
	install_idt(4, (uint32_t)isr4, 0x08, 0x8E);
	install_idt(5, (uint32_t)isr5, 0x08, 0x8E);
	install_idt(6, (uint32_t)isr6, 0x08, 0x8E);
	install_idt(7, (uint32_t)isr7, 0x08, 0x8E);
	install_idt(8, (uint32_t)isr8, 0x08, 0x8E);
	install_idt(9, (uint32_t)isr9, 0x08, 0x8E);
	install_idt(10, (uint32_t)isr10, 0x08, 0x8E);
	install_idt(11, (uint32_t)isr11, 0x08, 0x8E);
	install_idt(12, (uint32_t)isr12, 0x08, 0x8E);
	install_idt(13, (uint32_t)isr13, 0x08, 0x8E);
	install_idt(14, (uint32_t)isr14, 0x08, 0x8E);
	install_idt(15, (uint32_t)isr15, 0x08, 0x8E);
	install_idt(16, (uint32_t)isr16, 0x08, 0x8E);
	install_idt(17, (uint32_t)isr17, 0x08, 0x8E);
	install_idt(18, (uint32_t)isr18, 0x08, 0x8E);
	install_idt(19, (uint32_t)isr19, 0x08, 0x8E);
	install_idt(20, (uint32_t)isr20, 0x08, 0x8E);
	install_idt(21, (uint32_t)isr21, 0x08, 0x8E);
	install_idt(22, (uint32_t)isr22, 0x08, 0x8E);
	install_idt(23, (uint32_t)isr23, 0x08, 0x8E);
	install_idt(24, (uint32_t)isr24, 0x08, 0x8E);
	install_idt(25, (uint32_t)isr25, 0x08, 0x8E);
	install_idt(26, (uint32_t)isr26, 0x08, 0x8E);
	install_idt(27, (uint32_t)isr27, 0x08, 0x8E);
	install_idt(28, (uint32_t)isr28, 0x08, 0x8E);
	install_idt(29, (uint32_t)isr29, 0x08, 0x8E);
	install_idt(30, (uint32_t)isr30, 0x08, 0x8E);
	install_idt(31, (uint32_t)isr31, 0x08, 0x8E);

}

// Called when when a error fires
void 
isr_interrupted(registers_t* reg)
{
	if(reg->interrupt_id<32)
	{
		printk("[NOTE] Error fired: ");
		printk(exception_messages[reg->interrupt_id]);
	}
}
