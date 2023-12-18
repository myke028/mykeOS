#ifndef _PAGE_H_
#define _PAGE_H_

#include "types.h"

#define FourKBOUNDRY 4096



typedef struct PageDirectoryEntry{
    union{
        uint8_t val[4];
        struct{
            unsigned int present : 1;         // Page present in memory
            unsigned int read_write : 1;     // Read/write access
            unsigned int user_supervisor : 1; // User/supervisor mode
            unsigned int write_through : 1;  // Write-through caching
            unsigned int cache_disabled : 1;  // Cache disabled
            unsigned int accessed : 1;       // Page accessed
            unsigned int dirty : 1;          // Page dirty
            unsigned int page_size : 1;      // Page size (0 for 4 KB)
            unsigned int globalI : 1;         // Global page
            unsigned int available : 3;      // Available for software use
            unsigned int page_table_base : 20; // Page table base address
        }__attribute((__packed__));
        struct{
            unsigned int present : 1;         // Page present in memory
            unsigned int read_write : 1;     // Read/write access
            unsigned int user_supervisor : 1; // User/supervisor mode
            unsigned int write_through : 1;  // Write-through caching
            unsigned int cache_disabled : 1;  // Cache disabled
            unsigned int accessed : 1;       // Page accessed
            unsigned int dirty : 1;          // Page dirty
            unsigned int page_size: 1;
            unsigned int global : 1;         // Global page
            unsigned int available : 3;      // Available for software use
            unsigned int PTAI : 1;      // Page size (0 for 4 KB)

            unsigned int reserved: 9;      // Available for software use
            unsigned int page_base : 10; // Page base address (physical address of the 4 KB page)
        }__attribute((__packed__));
    };
} PageDirectoryEntry;








typedef struct PageTableEntry {
        unsigned int present : 1;         // Page present in memory
        unsigned int read_write : 1;     // Read/write access
        unsigned int user_supervisor : 1; // User/supervisor mode
        unsigned int write_through : 1;  // Write-through caching
        unsigned int cache_disabled : 1;  // Cache disabled
        unsigned int accessed : 1;       // Page accessed
        unsigned int dirty : 1;          // Page dirty
        unsigned int PTAI : 1;      // Page size (0 for 4 KB)
        unsigned int globalI : 1;         // Global page
        unsigned int available : 3;      // Available for software use
        unsigned int page_table_base : 20; // Page table base address

    } __attribute((__packed__)) PageTableEntry;




PageTableEntry page_table[1024] __attribute__((aligned (FourKBOUNDRY))); // Assuming 1024 entries in the page table
PageDirectoryEntry page_directory[1024] __attribute__((aligned (FourKBOUNDRY))); // Assuming 1024 entries in the page directory



void initializePage();
void setPageDirectory(int index);


#endif
