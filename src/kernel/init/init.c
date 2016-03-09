// init.c
// Written by Harry Rigg
// Starts base system up with nice messages

#include <kernel/init/init.h>

// Starts system
void 
init_system(multiboot_info_t* bi)
{
	// Start display
	vga_init();
	printk(" KiteOS V1.0 --- Initializing \n");
	// PIT-less wait to show user boot
	for(int i=0;i<64821125;i++);
	vga_color(0x3, 0x0);
	printk("-- STARTING LOWLEVEL KERNEL --\n");
	vga_color(0x5, 0x0);
	printk("!* Initiating GDT\n");
	gdt_init();
	printk("!* Initiating IDT\n");
	idt_init();
	printk("!* Installing Exceptions\n");
	isr_init();
	vga_color(0x4, 0x0);
	printk("*** ENTERTED PROTECTED MODE ***\n");
	vga_color(0x5, 0x0);
	printk("!* Initiating IRQ\n");
	irq_init();
	printk("!* Starting PIT\n");
	pit_init();
	printk("!* Starting RTC\n");
	rtc_init();
	printk("!* Restoring Interrupts\n");
	__asm__ __volatile__ ("sti");
	vga_color(0x3, 0x0);	
	printk("-- STARTING LOWLEVEL DRIVERS --\n");
	vga_color(0x5, 0x0);
	printk("!* Starting physical memory manager\n");
	kalloc_init((void*)bi->mmap_addr, (unsigned long)bi->mmap_length);
	printk("!* Starting keyboard driver\n");
	kb_init();
	printk("!* Starting IDE driver\n");
	ide_init(0x1F0, 0x3F6, 0x170, 0x366);
	vga_color(0x4, 0x0);
	printk("*** Initialized system successfully ***\n");
}
