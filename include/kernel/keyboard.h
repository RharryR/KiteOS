#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <kernel.h>
#include <irq.h>
#include <display.h>
#include <pmm.h>

char* keyboard_readline();
uint8_t keyboard_wait_for_key();
void keyboard_setup();

#endif
