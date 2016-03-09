#include <stdint.h>
#include <kernel/multiboot.h>
#include <kernel/init/init.h>
#include <kernel/drivers/video/vga.h>

/* Called from boot.asm */
void kernel_main(multiboot_info_t* bi, uint32_t magic)
{
	init_system(bi);
	sleep(28);
	vga_init();
	ext2_init();
}
