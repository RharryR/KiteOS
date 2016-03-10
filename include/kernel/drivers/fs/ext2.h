// ext2.c
// Written by Harry Rigg
// A ext2 filesystem driver
#ifndef EXT2_H
#define EXT2_H

#include <stdint.h>
#include <kernel/drivers/disk/ide.h>
#include <kernel/mem/kalloc.h>
#include <string.h>
#include <kernel/utils/terminal.h>

struct superblock
{
uint32_t s_inodes_count;
uint32_t s_blocks_count;
uint32_t s_r_blocks_count;
uint32_t s_free_blocks_count;
uint32_t s_free_inodes_count;
uint32_t s_first_data_block;
uint32_t s_log_block_size;
uint32_t s_log_frag_size;
uint32_t s_blocks_per_group;
uint32_t s_frags_per_group;
uint32_t s_inodes_per_group;
uint32_t s_mtime;
uint32_t w_wtime;
uint16_t s_mnt_count;
uint16_t s_max_mnt_count;
uint16_t s_magic;
uint16_t s_state;
uint16_t s_errors;
uint16_t s_minor_rev;
uint32_t s_last_check;
uint32_t s_checkinterval;
uint32_t s_creator_os;
uint32_t s_rev_level;
uint16_t s_def_resuid;
uint16_t s_def_resgid;
uint32_t s_first_inode;
uint16_t s_inode_size;
uint16_t s_block_group_nr;
uint32_t s_feature_compat;
uint32_t s_feature_incompat;
uint32_t s_feature_ro_compat;
char s_uuid[16];
char s_volume_name[16];
uint32_t s_algo_bitmap;
uint8_t s_prealloc_blocks;
uint8_t s_prealloc_dir_blocks;
uint16_t align;
char s_journal_uuid[16];
uint32_t s_journal_inum;
uint32_t s_journal_dev;
uint32_t s_last_orphan;
uint32_t s_hash_seed1;
uint32_t s_hash_seed2;
uint32_t s_hash_seed3;
uint32_t s_hash_seed4;
uint8_t s_def_hash_version;
char padding[3];
uint32_t s_default_mount_options;
uint32_t s_first_meta_bg;
};

struct bgdt
{
uint32_t bg_block_bitmap;
uint32_t bg_inode_bitmap;
uint32_t bg_inode_table;
uint16_t bg_free_blocks_count;
uint16_t bg_free_inodes_count;
uint16_t bg_used_dirs_count;
uint16_t bg_pad;
};

struct inode
{
uint16_t i_mode;
uint16_t i_uid;
uint32_t i_size;
uint32_t i_atime;
uint32_t i_ctime;
uint32_t i_mtime;
uint32_t i_dtime;
uint16_t i_gid;
uint16_t i_links_count;
uint32_t i_blocks;
uint32_t i_flags;
uint32_t i_osd1;
uint32_t i_block0;
uint32_t i_block1;
uint32_t i_block2;
uint32_t i_block3;
uint32_t i_block4;
uint32_t i_block5;
uint32_t i_block6;
uint32_t i_block7;
uint32_t i_block8;
uint32_t i_block9;
uint32_t i_block10;
uint32_t i_block11;
uint32_t i_block12;
uint32_t i_block13;
uint32_t i_block14;
uint32_t i_generation;
uint32_t i_file_acl;
uint32_t i_dir_acl;
uint32_t i_faddr;
char osd2[12];
};

struct dir_entry
{
uint32_t inode;
uint16_t rec_len;
uint8_t name_length;
uint8_t filetype;
};

uint8_t device=0;

struct superblock *sbi;

#endif
