//change
#ifndef IDT_H
#define IDT_H
#ifndef ASM

#include "lib.h"

void exception_log(int vector_no);
void idt_init();


#endif // asm
#endif