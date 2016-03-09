#ifndef LIBC_STRING_H
#define LIBC_STRING_H
#include <stdint.h>

int memcmp(const void*, const void*, size_t);
void* memcpy(void* __restrict, const void* __restrict, size_t);
void* memset(void*, int, size_t);
uint16_t *memsetw(uint16_t*, uint16_t, size_t);
size_t strlen(const char*);

#endif
