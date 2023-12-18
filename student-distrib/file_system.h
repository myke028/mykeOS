#ifndef _FILESYSTEM_H
#define _FILESYSTEM_H

#include "lib.h"

#define FILENAME_LEN 32
#define BYTES 4096


typedef struct dentry {
    int8_t filename [FILENAME_LEN];
    int32_t filetype;
    int32_t inode_num;
    int8_t reserved [24];
} dentry;

typedef struct boot_block {
    int32_t dir_count;
    int32_t inode_count;
    int32_t data_count;
    int8_t reserved [52];
    dentry direntries [63];
} boot_block;

typedef struct inode {
    int32_t length;
    int32_t data_block_num [1023];
} inode;

boot_block* filesys_base_ptr;
uint32_t inode_base_ptr;
uint32_t datablocks_base_ptr;







int32_t open_dir ();
int32_t open_file ();
int32_t close_dir ();
int32_t close_file ();
int32_t read_dir ();
int32_t read_file ();
int32_t write_dir ();
int32_t write_file ();


int32_t read_dentry_by_name(const uint8_t* fname, dentry* dentry);
int32_t read_dentry_by_index(uint32_t index, dentry* dentry);
int32_t read_data(uint32_t inode_num, uint32_t offset, uint8_t* buf, uint32_t length);






#endif
