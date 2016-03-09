#ifndef DISPLAY_H
#define DISPLAY_H
#include <kernel.h>
#include <string.h>
#include <system.h>

int32_t style;
uint32_t crs_x, crs_y;
uint16_t *text_ptr;

void display_scroll_screen();
void display_update_cursor();
void display_clear_screen();
void display_print_char(uint8_t c);
void display_print_string(uint8_t* text);
void display_set_style(uint8_t text, uint8_t back);
void display_set_crs(int x, int y);
void display_nl();
void display_print_len(uint8_t* text, size_t size);
void display_setup();

#endif
