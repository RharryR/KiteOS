#ifndef STRING_H
#define STRING_H
#include <kernel.h>

size_t strlen(uint8_t* str);
void* memcpy(void* dest, void* ptr, size_t count);
void* strcpy(void* dest, uint8_t* str);
void* memset(void* dest, uint16_t val, size_t count);
uint16_t* memsetw(uint16_t* dest, uint16_t val, size_t count);
uint16_t streql(uint8_t* str, uint8_t* cmp);

#endif
