// pit.c
// Written by Harry Rigg
// Driver for PIT (Programmable Interrupt Timer)
#ifndef PIT_H
#define PIT_H

#include <stdint.h>
#include <kernel/mem/register.h>
#include <kernel/init/irq.h>

size_t pit_clocks;

void 
pit_interrupt(registers_t* reg);

void 
pit_freq(uint32_t freq);

void 
pit_init();

void
sleep(size_t ticks);

#endif
