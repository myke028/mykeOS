#define ASM 1

.globl keyboard_interrupt, rtc_interrupt

keyboard_interrupt:
    pushal
    pushfl
    call keyboard_handler
    popfl   
    popal
    iret

rtc_interrupt:
    pushal
    pushfl
    call rtc_handler
    popfl
    popal
    iret
