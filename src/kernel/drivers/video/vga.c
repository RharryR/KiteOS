// vga.c
// Written by Harry Rigg
// A VGA driver. Currently only supports text, but will support graphics in the future.

#include <kernel/drivers/video/vga.h>

// Scrolls the screen if the cursor has exceed the screen size
void 
scroll_screen()
{
	uint32_t blank,tmp;
	blank=0x20|(style<<8);
	if(crs_y >= 25)
	{
		tmp=crs_y-25+1;
		memcpy(text_ptr, text_ptr+tmp*80, (25-tmp)*80*2);
		memsetw(text_ptr+(25-tmp)*80, blank, 80);
		crs_y=25-1;
	}
}

// Updates hardware cursor position
void 
update_hw_cursor()
{
	uint32_t tmp;
	tmp = crs_y * 80 + crs_x;
	outb(0x3D4, 14);
	outb(0x3D5, tmp >>8);
	outb(0x3D4, 15);
	outb(0x3D5, tmp);
}

// Clears the screen
void 
clear_screen()
{
	uint32_t blank;
	uint32_t i;
	blank = 0x20| (style << 8);
	for(i=0;i<25;i++)
		memsetw(text_ptr+i*80, blank, 80);
	crs_x=0;
	crs_y=0;
	update_hw_cursor();
}

// Prints a char
void 
vga_putch(uint8_t c)
{
	uint16_t *loc;
	uint32_t att=style<<8;
	if(c == 0x08)
	{
		if(crs_x !=0) crs_x--;
	}else if(c == 0x09)
	{
		crs_x=(crs_x + 8)&-(8-1);
	}else if(c == '\r')
	{
		crs_x=0;
	}else if(c == '\n')
	{
		crs_x=0;
		crs_y++;
	}else if(c >= ' ')
	{
		loc=text_ptr + (crs_y * 80 + crs_x);
		*loc=c | att;
		crs_x++;
	}
	
	if(crs_x >= 80)
	{
		crs_x = 0;
		crs_y++;
	}
	scroll_screen();
	update_hw_cursor();
}

// Prints a string
void 
vga_print(char* text)
{
	uint32_t i;
	for(i=0;i<strlen(text);i++) vga_putch(text[i]);
}

// Sets text and and background color
void 
vga_color(uint8_t text, uint8_t back)
{
	style=(back<<4)|(text&0x0f);
}

// Sets the cursor position 
void 
vga_crs(int x, int y)
{
	crs_x = x;
	crs_y = y;
	update_hw_cursor();
}

// Initiates VGA driver
void 
vga_init()
{	
	style = 0x0F;
	crs_x=0; crs_y=0;
	text_ptr=(uint16_t*)0xB8000;
	clear_screen();
}
