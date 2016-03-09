// vga.c
// Written by Harry Rigg
// A VGA driver. Currently only supports text, but will support graphics in the future.

#ifndef VGA_H
#define VGA_H

#include <stdint.h>
#include <kernel/sys/io.h>
#include <string.h>

int32_t style;
uint32_t crs_x, crs_y;
uint16_t* text_ptr;

void 
vga_putch(uint8_t c);

void 
vga_print(char* text);

void 
vga_color(uint8_t text, uint8_t back);

void 
vga_crs(int x, int y);

void 
vga_init();

#endif
