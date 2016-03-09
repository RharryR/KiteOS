// isr.c
// Written by Harry Rigg
// Installs exeception handlers on the system
#ifndef ISR_H
#define ISR_H

#include <stdint.h>
#include <kernel/mem/register.h>
#include <kernel/init/idt.h>

void 
isr_init();

void 
isr_interrupted(registers_t* reg);

#endif
