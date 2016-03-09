#ifndef SANDBOX_H
#define SANDBOX_H
#include <display.h>
#include <math.h>
#include <multiboot.h>
#include <drivers/pit.h>
#include <keyboard.h>

void start_mem_sandbox(multiboot_info_t* bi);

#endif
