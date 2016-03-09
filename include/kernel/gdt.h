#ifndef GDT_H
#define GDT_H

#include<kernel.h>
#include<display.h>

struct gdt_entry
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;	
}__attribute__((packed));

struct gdt_ptr
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

struct gdt_entry gdt[3];
struct gdt_ptr g_pointer;

extern void flush_gdt();

void gdt_set_gate(int32_t index, size_t base, size_t limit, uint8_t access, uint8_t gran);
void gdt_setup();

#endif
