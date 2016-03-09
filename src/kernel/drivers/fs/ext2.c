// ext2.c
// Written by Harry Rigg
// A ext2 filesystem driver

#include <kernel/drivers/fs/ext2.h>

// Converts block address to LBA
uint32_t 
block_to_lba(uint32_t block)
{
	return block * 2;
}

// Returns BGDT for a specified block group
struct bgdt 
get_blockgroup_info(uint32_t bg_addr)
{
	struct bgdt  *out = kmalloc(sizeof(struct bgdt));
	void* fb = kmalloc(1024);
	ide_read(block_to_lba(2), device, fb, 2);
	void* location = fb+ (bg_addr * 32);
	memcpy(out, location, 32);
	return *out;
}

// Returns a inode struct for the specified inode
struct inode
get_inode(uint32_t inode)
{
	uint32_t blockgroup = (inode - 1) / sbi->s_inodes_per_group;
	uint32_t table_index = (inode - 1) % sbi->s_inodes_per_group;
	
	struct bgdt bgi = get_blockgroup_info(blockgroup);
	
	uint32_t add = table_index / 8;
	
	void* buffer = kmalloc(1024);
	ide_read(block_to_lba(bgi.bg_inode_table + add), device, buffer, 2);
	
	struct inode* ret = kmalloc(sizeof(struct inode));
	memcpy(ret, buffer + ((table_index % 8) * 128), sizeof(struct inode));
	return *ret;
}

// Places the superblock into sbi
void 
parse_superblock()
{
	void* sb_buff = kmalloc(1024);
	
	// Read in superblock
	ide_read(block_to_lba(1), device, sb_buff, 2);
	memcpy(sbi, sb_buff, 1024);
	kfree(sb_buff);
}

// Verifies the superblock, this detects to see if a ext2 fs is present
int 
verify_superblock()
{
	if(sbi->s_magic != 0xEF53)
	{
		knl();
		printk("KiteEXT2: Invalid magic-number found when reading ext2 FS.");
		return 1;
	}
	return 0;
}

// Starts KiteEXT2 on the specified IDE device
int 
ext2_init(uint8_t adevice)
{
	sbi = kmalloc(sizeof(struct superblock));
	parse_superblock();
	if(verify_superblock())
		return 1;
	return 0;
}





