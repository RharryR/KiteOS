#ifndef ATAPIO_H
#define ATAPIO_H
#include <kernel.h>
#include <system.h>
#include <drivers/pit.h>
#include <display.h>
#include <math.h>
#include <pmm.h>

void ide_init(uint16_t pri, uint16_t pcr, uint16_t sec, uint16_t scr);
void ide_read(uint32_t lba, uint8_t device, void* loc, uint8_t sectors);
void ide_write(uint32_t lba, uint8_t device, char* in);

#endif
