#ifndef ISR_H
#define ISR_H
#include <kernel.h>
#include <display.h>
#include <idt.h>
void isr_setup();
void handle_isr_fault(struct regs* r);

#endif
