
#include "keyboard.h"
#include "terminal.h"
#include "lib.h"

#define KEYBOARD_IRQ 1
#define lShiftPressed 0x2A
#define CapsPressed 0x3A
#define lCtrlPressed 0x1D
#define lShiftReleased 0xAA
#define CapsOff 0xBA
#define lCtrlOff 0x9D
#define enter 0x1C
#define backSpace 0x0E


int caps = 0;
int shift = 0;
int ctrl = 0;
int endl = 0;


/*
Respective key board interrupt print characters
*/

char boardLower[board_size] =  
{
    NULL, NULL , '1', '2', '3', '4', '5', '6', 
    '7', '8', '9', '0', '-', '=', '\b', '\t',
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i',
    'o', 'p', '[',']', '\n',NULL , 'a', 's', 'd',
    'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', NULL
     , '\\','z' , 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', NULL, '*', NULL , ' ', NULL 
};

char boardCaps[board_size] =  
{
    NULL, NULL , '1', '2', '3', '4', '5', '6', 
    '7', '8', '9', '0', '-', '=', '\b', '\t',
    'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I',
    'O', 'P', '[',']', '\n',NULL , 'A', 'S', 'D',
    'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', '`', NULL
     , '\\','Z' , 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/', NULL, '*', NULL , ' ', NULL 
};


char boardShift[board_size] =  
{
    NULL, NULL , '!', '@', '#', '$', '%', '^', 
    '&', '*', '(', ')', '_', '+', '\b', '\t',
    'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I',
    'O', 'P', '{','}', '\n',NULL , 'A', 'S', 'D',
    'F', 'G', 'H', 'J', 'K', 'L', ':', '\"', '`~', NULL
     , '?','Z' , 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', NULL, '*', NULL , ' ', NULL 
};





// char board[board_size] =  
// {
//     NULL, 'e', '1', '2', '3', '4', '5', '6', 
//     '7', '8', '9', '0', '-', '=', 'b', 't',
//     'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I',
//     'O', 'P', '[',']', 'e', 'l', 'A', 'S', 'D',
//     'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', '`',
//     's', '\\', 'Z', 'X', 'C', 'V', 'B', 'N', 'M'
// };

/* keyboard_init
    Input: void
    Output: void
    Description: initializes the keyboard device and calls the enable_irq fxn on the keyboard IRQ number.
*/
void keyboard_init() {
    enable_irq(KEYBOARD_IRQ);
}

/*
#define lShiftPressed 0x2A
#define CapsPressed 0x3A
#define lShiftReleased 0xAA
#define CapsOff 0xBA
#define lCtrlPressed 0x1E
#define lCtrlOff 0x9D


int caps;
int shift;
int ctrl;
*/
/* keyboard_handler
    Input: void
    Output: void
    Description: logic for keyboard input and reflect onto graphics
*/
void keyboard_handler () {
    int skip = 0;
    // cli();
    uint8_t key_port = inb(board_port);
    //printf("This is the scancode: %d", key_port);
    if(key_port < board_size || key_port == lShiftReleased || key_port == lCtrlOff || key_port == CapsPressed || key_port == lShiftPressed || key_port == lCtrlPressed || key_port == CapsOff) {
        if(key_port == lShiftPressed) {
            shift = 1;
        }

        if(key_port == CapsPressed) {   
            caps = 1;

        }
        if(key_port == lCtrlPressed) {
            ctrl = 1;

        }

        if(key_port == lShiftReleased) {
            shift = 0;
        }

        if(key_port ==  CapsOff) {
            caps = 0;
        }

        if(key_port == lCtrlOff) {
            ctrl = 0;
        }
      
    

        if(ctrl && (boardLower[key_port] == 'l' || boardCaps[key_port] == 'L' || boardShift[key_port] == 'L')) {
            endl = 0;
            clear();
          
        } else {
            if(key_port == backSpace) {
                if(arr[0].buf[0] != '\0' ) {
                    putc(boardLower[key_port]);
                    arr[0].buf[arr[0].bufPos]  = '\0';



                }
            }
            if(key_port == enter) {
                endl = 1;
            } else {
                endl = 0;
            }
            if(caps && arr[0].bufPos < buffSize && !shift) {
                putc(boardLower[key_port]);
                arr[0].buf[++arr[0].bufPos]  = boardLower[key_port];

                

            }
            if(shift && arr[0].bufPos < buffSize && !caps) {
                putc(boardShift[key_port]);
                arr[0].buf[++arr[0].bufPos]  = boardLower[key_port];


            }
            if(!shift && !caps && arr[0].bufPos < buffSize) {
                putc(boardLower[key_port]);
                arr[0].buf[++arr[0].bufPos]  = boardLower[key_port];


            }

        }

    }

    send_eoi(KEYBOARD_IRQ);

   
    // sti();

}
