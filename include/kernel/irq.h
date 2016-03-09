#ifndef IRQ_H
#define IRQ_H

#include <kernel.h>
#include <system.h>
#include <idt.h>

void *irq_handlers[16];
void irq_install_handler(uint32_t loc, void (*handler)(struct regs* r));
void irq_uninstall_handler(uint32_t loc);
void irq_remap();
void irq_setup();
void handle_irq(struct regs* r);

#endif
