#ifndef IDT_H
#define IDT_H
#include <kernel.h>
#include <string.h>

struct idt_entry
{
	uint16_t base_lo;
    uint16_t sel;
    uint8_t always0;
    uint8_t flags;
    uint16_t base_hi;
}__attribute__((packed));

struct idt_ptr
{
    uint16_t limit;
    uint32_t base;
}__attribute__((packed));

struct idt_entry idt[256];
struct idt_ptr i_pointer;

extern void load_idt();

void idt_set_gate(uint8_t index, size_t base, uint16_t sel, uint8_t flags);
void idt_setup();

#endif
