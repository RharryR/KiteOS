#ifndef PMM_H
#define PMM_H
#include <kernel.h>
#include <system.h>
#include <string.h>
#include <display.h>
#include <math.h>

void pmm_init(void* mmloc, unsigned long mmsize);
void* pmm_allocate(size_t size);
void* pmm_calloc(size_t size);
void* pmm_realloc(void* ptr, size_t nsize);
void pmm_free(void* alloc);

#endif
