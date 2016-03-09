// rtc.c
// Written by Harry Rigg
// Driver for RTC (Real Time Clock) and CMOS
#ifndef RTC_H
#define RTC_H

#include <stdint.h>
#include <kernel/sys/io.h>
#include <kernel/init/irq.h>

void 
rtc_interrupt(registers_t* reg);

void 
rtc_init();

#endif
