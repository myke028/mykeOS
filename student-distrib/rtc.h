/* Header file for the RTC module. includes floating definitions to use for implementation
*/

#ifndef _RTC_H
#define _RTC_H

#include "i8259.h"

#define board_size 51
#define board_search 52
#define board_port 0x60

void rtc_init();
void rtc_handler();

int rtc_read();
int rtc_write();
int rtc_open(const uint8_t* filename);

double log2(double a);

uint32_t nodedu;
int my_interrupt;

#endif
