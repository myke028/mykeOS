#include "lib.h"
#include "file_system.h"



// get base ptr of inode (mbi, mod_start)

//ken carson destroy lonely playboi carti


/*
Function: read_dentry_by_name
Inputs: fname, dentry
Output: int32_t
Description: Search for a directory entry by given filename in file system, fills the provided dentry structure with the relevant details, and returns 0 on success or -1 if the filename is not found or invalid.
*/
int32_t read_dentry_by_name(const uint8_t* fname, dentry* dentry) {
    int dir_count = filesys_base_ptr->dir_count;
    if(strlen(dentry->filename) > 32 || strlen(dentry->filename) < 0 ) {
        return -1;
    }
    int i = 0;
    for(i = 0; i < dir_count; i++) {
        if(strncmp(fname, filesys_base_ptr->direntries[i].filename, FILENAME_LEN) == 0) {
            read_dentry_by_index((uint32_t)i, dentry);
            return 0;
        }

    }

    return -1;
}

/*
Function: read_dentry_by_index
Inputs: index, dentry
Output: int32_t
Description: Retrieves directory entry information based on the given index, populates the provided dentry structure with the corresponding details, and returns 0 for success or -1 if the index is out of bounds.
*/
int32_t read_dentry_by_index(uint32_t index, dentry* dentry) {
    if(index < 0 || index >= 64) {
        return -1;
    }
    strcpy(dentry->filename, filesys_base_ptr->direntries[index].filename);
    dentry->filetype = filesys_base_ptr->direntries[index].filetype;
    dentry->inode_num = filesys_base_ptr->direntries[index].inode_num;

    return 0;

}

/*
Function: read_data
Inputs: inode_num, offset, buf, length
Output: int32_t
Description: Reads data from a file's inode, starts at a given offset, and stores in the given buffer up to the specified length. Adjusts the length if it exceeds the file size, and the actual number of bytes that is read gets returned. The data is also copied in 4096-byte chunks
*/

int32_t read_data(uint32_t inode_num, uint32_t offset, uint8_t* buf, uint32_t length) {

    // uint32_t nbytes = 0;
    
    inode* inode_curr_ptr = (void*)(inode_base_ptr + ((inode_num) * BYTES));
    
    if((inode_curr_ptr)->length < length) {
        length =inode_curr_ptr->length;
    }

    int countDown = length;
    int i = 0;
    while(countDown > 0) {
        int cur_data = inode_curr_ptr->data_block_num[i] * 4096 + datablocks_base_ptr; //////////////////
        if(countDown < 4096) {
            memcpy(buf,cur_data,countDown);
            return length;
        } else {
            memcpy(buf, cur_data,4096);
            countDown -=4096;
            buf+= 4096;
            if(countDown < 0) {
                return length;
            }
            i++;

        }
    }

/*

add (inode num * 4096) to base ptr = curr_inode_ptr
if(curr_inoid_ptr->length < length){
    length = curr_inoid_ptr->length
}
int countDown = length;
i=0;
while countDown > 0
    {
        cur_data = inode->data_block_num[i]*4096 + data_blocks_base_ptr
        if(countDown < 4096) {
            memcpy(buf, cur_data, countDown)
            return length;
        } else {
            memcpy(buf, cur_data, 4096)
            countDown -= 4096;
            buf += 4096;
            if(countDown <= 0) {
                return length;
            }
            i++;

        }
        
    }
*/
}


/*
Function: open_dir
Inputs: none
Output: int32_t
Description: This function is designed to open a directory and returns 0 for success.
*/
int32_t open_dir (){ 
    return 0;
}

/*
Function: open_file
Inputs: none
Output: int32_t
Description: This function is designed to open a file and returns 0 for success.
*/
int32_t open_file (){ 
    return 0;
}

/*
Function: close_dir
Inputs: none
Output: int32_t
Description: This function is designed to close a directory and returns 0 for success.
*/
int32_t close_dir (){ 
    return 0;
}

/*
Function: close_file
Inputs: none
Output: int32_t
Description: This function is designed to close a file and returns 0 for success.
*/
int32_t close_file (){ 
    return 0;
}

/*
Function: open_file
Inputs: fd, buf, nbytes
Output: int32_t
Description: This function is designed to read from a directory and returns 0 for success.
*/
int32_t read_dir (int32_t fd, void* buf, int32_t nbytes){
    
    return 0;
}

/*
Function: read_file
Inputs: fd, buf, nbytes
Outputs: int32_t
Description: Reads data from the file descriptor (fd) file; first retrieves the directory entry for frame0.txt via read_dentry_by_name to get the correct inode number; next it uses read_data to read data from the inode starting at offset 0 and stores it in the buf, up to the specified number of bytes nbytes.
*/
int32_t read_file (int32_t fd, void* buf, int32_t nbytes){
    dentry d;
    read_dentry_by_name((uint8_t*)"frame0.txt", &d);

    read_data(d.inode_num, 0, buf, nbytes);
    /*
    read dentry via name -> gets inode number
    call read_data();


    */
}

/*
Function: write_dir
Inputs: none
Output: int32_t
Description: This function is designed to write to a directory and returns -1 for unsupported.
*/
int32_t write_dir (){
    return -1;
}

/*
Function: write_file
Inputs: none
Output: int32_t
Description: This function is designed to write to a file and returns -1 for unsupported.
*/
int32_t write_file (){
    return -1;
}
