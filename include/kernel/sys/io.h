// io.h
// Written by Harry Rigg
// General port input and output functions
#ifndef IO_H
#define IO_H

#include <stdint.h>

uint8_t 
inb(uint16_t port);

void 
outb(uint16_t port, uint8_t data);

uint16_t 
inw(uint16_t port);

void 
outw(uint16_t port, uint16_t data);

#endif
