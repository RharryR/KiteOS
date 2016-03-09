// terminal.c
// Written by Harry Rigg
// Contains basic terminal functions
#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdint.h>
#include <kernel/drivers/video/vga.h>

void 
printk(char* text);

void
knl();

#endif

