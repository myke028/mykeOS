#ifndef _TERMINAL_H
#define _TERMINAL_H

#define buffSize 128
#define numterm 1
void terminal_initialization();
int terminal_write();
int terminal_read();

typedef struct terminal_t {
    int curx;
    int cury;
    int bufPos;
    char buf[buffSize];


} term;


term arr[numterm];


#endif