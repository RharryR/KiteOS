#ifndef INIT_H
#define INIT_H
#include <kernel.h>
#include <display.h>
#include <gdt.h>
#include <idt.h>
#include <isr.h>
#include <irq.h>
#include <math.h>
#include <drivers/pit.h>
#include <string.h>
#include <multiboot.h>
#include <drivers/rtc.h>
#include <pmm.h>
#include <keyboard.h>
#include <drivers/atapio.h>

void init_system();

#endif
