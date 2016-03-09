// ide.c
// Written by Harry Rigg
// A IDE driver. Support's ATA and ATAPI
// Note: I wrote this so I could learn about ATA. The real hdd driver will be written for AHCI and SATA
// Of course, this will stick around for compatibility and legacy reasons ;)
#ifndef IDE_H
#define IDE_H

#include <stdint.h>
#include <kernel/sys/io.h>
#include <kernel/init/irq.h>

uint8_t irq_fired;

struct ide_bus
{
	uint16_t base;
	uint16_t ctrl;
} buses[2];

struct ide_device
{
	uint8_t exist;
	uint8_t type;
	uint8_t bus;
	uint8_t drive;
	uint32_t size;
	char model[41];
	char serialnumber[21];
	char revision[9];
} devices[4];

void 
ide_init(uint16_t pri, uint16_t pcr, uint16_t sec, uint16_t scr);

void 
ide_read(uint32_t lba, uint8_t device, void* loc, uint8_t sectors);

void 
ide_write(uint32_t lba, uint8_t device, char* loc, uint8_t sectors);

#endif
