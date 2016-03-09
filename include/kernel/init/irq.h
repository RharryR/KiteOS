// irq.c
// Written by Harry Rigg
// Utilities to install irq handlers on the PIC
#ifndef IRQ_H
#define IRQ_H

#include <stdint.h>
#include <kernel/mem/register.h>
#include <kernel/sys/io.h>
#include <kernel/init/idt.h>

void 
install_irq(uint32_t loc, void (*handler)(registers_t* reg));

void 
uninstall_irq(uint32_t loc);

void 
remap();

void 
irq_init();

void 
irq_interrupted(registers_t* reg);

#endif
