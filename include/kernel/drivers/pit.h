#ifndef PIT_H
#define PIT_H
#include <kernel.h>
#include <math.h>
#include <display.h>
#include <irq.h>

size_t pit_ticks;
void pit_sleep(uint32_t tcks);
void pit_int(struct regs* r);
void pit_setup();

#endif
