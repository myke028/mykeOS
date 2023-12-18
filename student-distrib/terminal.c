#include "terminal.h"
#include "lib.h"

/**
 * Function: terminal_initialization
 * 
 * Description:
 * This function initializes an array of terminal structures to their default values.
 * Each element in the array `arr` represents a terminal and is initialized with
 * the current cursor position (curx and cury) set to 0 and the buffer position (bufPos)
 * also set to 0. This is typically used to prepare a set of terminals for use.
 * 
 * Inputs:
 * - None (assumes `arr` and `numterm` are global variables or available within the scope).
 * 
 * Outputs:
 * - None
 */

void terminal_initialization()  {
    int i = 0;
    for(i = 0; i < numterm; i++) {
        arr[i].curx = 0;
        arr[i].cury = 0;
        arr[i].bufPos = 0;

    }


}


/**
 * Function: terminal_write
 * 
 * Description:
 * This function writes data from a buffer to a specified terminal. It iterates
 * through the characters in the `buffer` and writes them to the terminal until
 * it encounters a null terminator ('\0') or reaches the specified `buffer_size`.
 * After writing, it updates the buffer position (bufPos) of the target terminal.
 * 
 * Inputs:
 * - buffer: A pointer to the character buffer containing the data to be written.
 * - buffer_size: The maximum number of characters to write from the buffer.
 * - term: The index of the target terminal in the 'arr' array.
 * 
 * Outputs:
 * - int
 * - If 'buffer' is NULL, the function returns without writing
 */

int terminal_write(char* buffer, int buffer_size , int term) {
    if(buffer == NULL) {
        return;
    }
    int i = 0;
    for(i = 0; i < buffer_size; i++) {
        if(buffer[i] == '/0') {
            break;
        } else {
            putc(buffer[i]);
        }
    }
    arr[term].bufPos = i;
    return i;

}

/**
 * Function: terminal_read
 * 
 * Description:
 * Reads characters from a terminal buffer into 'buffer' and updates the buffer position.
 * 
 * Inputs:
 * - buffer: Pointer to the destination buffer.
 * - buffer_size: Maximum characters to read.
 * - term: Target terminal index in 'arr'.
 * 
 * Outputs:
 * - Returns the number of characters read. (integer)
 * - Returns immediately if 'buffer' is NULL.
 */

int terminal_read(char* buffer, int buffer_size, int term) {
    int i = 0;
    if(buffer = NULL) {
        return;
    }
        memset(arr[term].buf, 0, buffer_size);
    if(buffer_size < buffSize) {
        for(i = 0; i < buffer_size; i++) {
            if(buffer[i] != '/0') {
                arr[term].buf[i] = buffer[i];
            } else {
                return;
            }
            

        }
        

    } else {
          for(i = 0; i < buffSize; i++) {
            if(buffer[i] != '/0') {
                arr[term].buf[i] = buffer[i];
            } else {
                return;
            }
            

        }
        


    }

    arr[term].bufPos = i;
    return i;
}


