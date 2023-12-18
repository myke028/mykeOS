#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

#ifndef ASM
    extern void keyboard_interrupt();
    extern void rtc_interrupt();
#endif

#endif