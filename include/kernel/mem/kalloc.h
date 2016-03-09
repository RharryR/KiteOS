// kalloc.c
// Written by Harry Rigg
// Kernel memory allocator
#ifndef KALLOC_H
#define KALLOC_H

#include <stdint.h>
#include <string.h>

typedef struct
{
uint8_t flags;
void* next_h;
void* prev_h;
} memzone_t;

typedef struct
{
	uint32_t size;
	unsigned long long int base;
	unsigned long long int len;
	uint32_t type;

} memory_map_entry_t;

void 
kalloc_init(void* mmloc, unsigned long mmsize);

void* 
kmalloc(size_t size);

void*
kcalloc(size_t size);

void*
krealloc(void* ptr, size_t nsize);

void 
kfree(void* alloc);

#endif
