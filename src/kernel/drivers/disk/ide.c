// ide.c
// Written by Harry Rigg
// A IDE driver. Support's ATA and ATAPI
// Note: I wrote this so I could learn about ATA. The real hdd driver will be written for AHCI and SATA
// Of course, this will stick around for compatibility and legacy reasons ;)

#include <kernel/drivers/disk/ide.h>

// Reads 256 words from the *ata* data port
void 
read_buffer(uint8_t bus, char* loc, uint8_t endianess)
{	
	if(endianess)
	{
		for(int i=0;i<512;i+=2)
		{
			uint16_t d = inw(buses[bus].base + 0x0);
			loc[i] = d >> 8;
			loc[i+1] = d;
		}
	
	}
	else
	{
		for(int i=0;i<512;i+=2)
		{
			uint16_t d = inw(buses[bus].base + 0x0);
			loc[i+1] = d >> 8;
			loc[i] = d;
		}
	}
}

// Called on primary bus interrupt
void
primary_interrupt(registers_t* reg)
{
	irq_fired=1;
	inb(0x1F7);
	outb(0xA0, 0x20);
	outb(0x20, 0x20);
}

// Called on secondary bus interrupt
void 
secondary_interrupt(registers_t* reg)
{
	irq_fired=1;
	inb(0x177);
	outb(0xA0, 0x20);
	outb(0x20, 0x20);
}


void 
ide_init(uint16_t pri, uint16_t pcr, uint16_t sec, uint16_t scr)
{
	irq_fired=0;
	// Some helpful variables
	uint8_t dev_c=0;
	uint8_t err=0;
	
	// Install channel data
	buses[0].base = pri;
	buses[0].ctrl = pcr;
	buses[1].base = sec;
	buses[1].ctrl = scr;
	
	// Install IRQ handlers
	install_irq(14, primary_interrupt);
	install_irq(15, secondary_interrupt);
	
	for(int i=0;i<2;i++)
		for(int j=0;j<2;j++)
		{
			uint8_t type=0;
			devices[dev_c].exist=0;
		
			// Select device
			outb(buses[i].base + 6, 0xA0 | (j << 4));
			
			// NULL out LBA and sectorcount
			outb(buses[i].base + 2, 0x0);
			outb(buses[i].base + 3, 0x0);
			outb(buses[i].base + 4, 0x0);
			outb(buses[i].base + 5, 0x0);
			
			// Send identify command
			outb(buses[i].base + 7, 0xEC);
			irq_fired=0;
			
			// Does the device exist?
			if(!inb(buses[i].base + 7)) continue;
			
			// Wait for ATA to be ready
			while(1)
			{
				uint8_t status = inb(buses[i].base+7);
				if(!(status & 0x80) && (status & 8)) break;
				if((status & 1)){err =1; break;};
				if(inb(buses[i].base+4) != 0 && inb(buses[i].base+5) != 0){err=1; break;}
			}
			
			// But, if it gave us a error, its not ATA, lets try identifing a ATAPI device
			if(err==1)
			{
				uint8_t lmi = inb(buses[i].base+4);
				uint8_t lhi = inb(buses[i].base+5);
				if(lmi == 0x14 && lhi == 0xEB) type =1;
				else continue;
				outb(buses[i].base +7, 0xA1);
				irq_fired = 0;
			}
			
			// Allocated identification buffer
			char* iden_buff = kmalloc(512);
			
			// Read in the identification buffer, with a endianess of 0
			read_buffer(i, iden_buff, 0);
			
			// The drive exists
			devices[dev_c].exist=1;
			
			// Set the type
			devices[dev_c].type = type;
			
			// Set the drive and bus it belongs too
			devices[dev_c].drive=j;
			devices[dev_c].bus=i;
			
			// Set drive size
			devices[dev_c].size = (int)iden_buff+120;
			
			// Copy strings (model, serial number and revision)
			// Model
			for(int k=i;k<40;k++)
			{
				devices[dev_c].model[k] = iden_buff[k+54];
			
			}
			devices[dev_c].model[40] = 0;
			
			// Serial Number
			for(int k=0;k<20;k++)
			{
				devices[dev_c].serialnumber[k] = iden_buff[k+20];
			}
			devices[dev_c].serialnumber[20] = 0;
			
			// Revision
			for(int k=0;k<8;k++)
			{
				devices[dev_c].revision[k] = iden_buff[k+46];
			}
			devices[dev_c].revision[8] = 0;
			
			// Next device
			dev_c++;
			
			// Free identification buffer
			kfree(iden_buff);
		}
		
}

// Reads a amount of sectors from the specified LBA off the specified device
void 
ide_read(uint32_t lba, uint8_t device, void* loc, uint8_t sectors)
{
	size_t offset=0;
	// Get the bus
	uint8_t bus = devices[device].bus;
	// Send the device
	outb(buses[bus].base + 6, 0xE0 | (devices[device].drive << 4) | ((lba >> 24)&0x0F));
	
	// NULL out
	outb(buses[bus].base + 1, 0x0);
	
	// Send parameters
	outb(buses[bus].base + 2, (uint8_t) sectors);
	outb(buses[bus].base + 3, (uint8_t) lba);
	outb(buses[bus].base + 4, (uint8_t) (lba >> 8));
	outb(buses[bus].base + 5, (uint8_t) (lba >> 16));
	
	irq_fired=0;
	
	// Send read command
	outb(buses[bus].base + 7, 0x20);
	
	// Read buffer
	for(int i =0;i<sectors;i++)
	{
		while(!irq_fired);
		irq_fired = 0;
		read_buffer(bus, loc+offset, 1);
		offset+=512;
	}
}

// Almost exactly the same as 'ide_read()' except data is taken from the buffer and placed on the drive
void 
ide_write(uint32_t lba, uint8_t device, char* loc, uint8_t sectors)
{
	// Get the bus
	uint8_t bus = devices[device].bus;
	// Send the device
	outb(buses[bus].base + 6, 0xE0 | (devices[device].drive << 4) | ((lba >> 24)&0x0F));
	
	// NULL out
	outb(buses[bus].base + 1, 0x0);
	
	// Send parameters
	outb(buses[bus].base + 2, (uint8_t) sectors);
	outb(buses[bus].base + 3, (uint8_t) lba);
	outb(buses[bus].base + 4, (uint8_t) (lba >> 8));
	outb(buses[bus].base + 5, (uint8_t) (lba >> 16));
	
	irq_fired=0;
	
	// Send write command
	outb(buses[bus].base + 7, 0x30);
	
	// Loop through the sectorcount
	for(int i=0;i<sectors;i++)
	{
		while(!irq_fired);
		irq_fired = 0;
		// Write buffer
		for(int i=0;i<512;i+=2)
		{
			outw(buses[bus].base + 0x0, loc[i] | (loc[i+1] << 8));
		}
	}
}
