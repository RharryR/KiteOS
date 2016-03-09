// init.c
// Written by Harry Rigg
// Starts base system up with nice messages
#ifndef INIT_H
#define INIT_H

#include <stdint.h>
#include <kernel/multiboot.h>
#include <kernel/init/irq.h>
#include <kernel/init/isr.h>
#include <kernel/init/idt.h>
#include <kernel/init/gdt.h>
#include <kernel/drivers/disk/ide.h>
#include <kernel/drivers/timing/pit.h>
#include <kernel/drivers/timing/rtc.h>
#include <kernel/mem/kalloc.h>
#include <kernel/utils/terminal.h>
#include <kernel/drivers/input/kb.h>

void 
init_system(multiboot_info_t* bi);

#endif
