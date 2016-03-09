// kb.c
// Written by Harry Rigg
// PS2 Keyboard driver
#ifndef KB_H
#define KB_H

#include <stdint.h>
#include <kernel/init/irq.h>

// Holds keys pressed
// Only use for text input
char* kb_buffer;

// Holds amount of keys pressed
// Only use for text input
uint64_t kb_count;

void 
kb_interrupt(registers_t* reg);

void 
kb_init();

#endif
