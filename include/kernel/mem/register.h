#ifndef REGISTER_H
#define REGISTER_H
#include <stdint.h>

typedef struct
{
    uint32_t gs, fs, es, ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t interrupt_id, err_code;
    uint32_t eip, cs, eflags, useresp, ss; 
}registers_t;

#endif
