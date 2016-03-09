#ifndef SYSTEM_H
#define SYSTEM_H
#include <kernel.h>

uint8_t inb(uint16_t _port);
void outb(uint16_t _port, uint8_t _data);
uint16_t inw(uint16_t port);
void outw(unsigned short _port, unsigned short data);

#endif
