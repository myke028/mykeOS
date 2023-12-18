#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include "i8259.h"

#define board_size 61
#define board_search 52
#define board_port 0x60

void keyboard_init();
void keyboard_handler();

#endif
