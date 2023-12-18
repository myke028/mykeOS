#include "page.h"


#define totSlots 1024
#define kernel 0x400000
#define vidMem 0xB8000
#define user 0x08000000



void initializePage() {
    int i = 0;
    setPageDirectory(i);
    for(i = 1; i < totSlots; i++) {
        if(i == 1) {
            page_directory[i].present = 1;
            page_directory[i].read_write = 1;
            page_directory[i].user_supervisor = 0;
            page_directory[i].write_through = 0;
            page_directory[i].cache_disabled = 1;
            page_directory[i].accessed = 0;
            page_directory[i].dirty = 0;
            page_directory[i].page_size = 1;
            page_directory[i].globalI = 1;
            page_directory[i].available = 0;
            page_directory[i].page_base = 1;

        } 
        // else if(i = 32) {
        //     page_directory[i].present = 0;
        //     page_directory[i].read_write = 1;
        //     page_directory[i].user_supervisor = 1;
        //     page_directory[i].write_through = 0;
        //     page_directory[i].cache_disabled = 1;
        //     page_directory[i].accessed = 0;
        //     page_directory[i].dirty = 0;
        //     page_directory[i].page_size = 1;
        //     page_directory[i].globalI = 0;
        //     page_directory[i].available = 0;
        //     page_directory[i].page_table_base = (int) user >> 12;

        // }  
        else {
            page_directory[i].present = 0;
            page_directory[i].read_write = 0;
            page_directory[i].user_supervisor = 0;
            page_directory[i].write_through = 0;
            page_directory[i].cache_disabled = 0;
            page_directory[i].accessed = 0;
            page_directory[i].dirty = 0;
            page_directory[i].page_size = 0;
            page_directory[i].globalI = 0;
            page_directory[i].available = 0;
           // page_directory[i].page_table_base = (int) page_table >> 12;

        }

    }
    int j;
    for(j = 0; j < totSlots; j++) {
        page_table[i].present = 0;
    }

          
    page_table[0xb8].present = 1;
    page_table[0xb8].read_write = 1;
    page_table[0xb8].user_supervisor = 0;
    page_table[0xb8].write_through = 0;
    page_table[0xb8].cache_disabled = 1;
    page_table[0xb8].accessed = 0;
    page_table[0xb8].dirty = 0;
    page_table[0xb8].PTAI = 0;
    page_table[0xb8].globalI = 0;
    page_table[0xb8].available = 0;
    page_table[0xb8].page_table_base = 0xB8;

    page_directory[0].present = 1;

// OS DEV IMPLEMENTATION https://wiki.osdev.org/Setting_Up_Paging
    asm volatile(
        "movl %0, %%eax             ;"
        "movl %%eax, %%cr3          ;"

        "movl %%cr4, %%eax          ;"
        "orl $0x00000010, %%eax     ;"
        "movl %%eax, %%cr4          ;"

        "movl %%cr0, %%eax          ;"
        "orl $0x80000000, %%eax     ;"
        "movl %%eax, %%cr0          ;"

        :  : "r"(page_directory): "eax" 
    );

}


void setPageDirectory(int i) {
    page_directory[i].present = 1;
    page_directory[i].read_write = 1;
    page_directory[i].user_supervisor = 0;
    page_directory[i].write_through = 0;
    page_directory[i].cache_disabled = 1;
    page_directory[i].accessed = 0;
    page_directory[i].dirty = 0;
    page_directory[i].page_size = 0;
    page_directory[i].globalI = 0;
    page_directory[i].available = 0;
    page_directory[i].page_table_base = (int) page_table >> 12;

}


//osdev
// void enable() {
// asm volatile {
// .text
// .globl loadPageDirectory
// loadPageDirectory:
// push %ebp
// mov %esp, %ebp
// mov 8(%esp), %eax
// mov %eax, %cr3
// mov %ebp, %esp
// pop %ebp
// ret

// }
// }
