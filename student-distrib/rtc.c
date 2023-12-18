//ken vs lone... who will win?

#include "rtc.h"
#include "lib.h"
#include "i8259.h"



#define RTC_IRQ 8
#define RTC_CMD_PORT 0x70



/* rtc_init
    Inputs: void
    Outputs: void
    Description: Initializes the RTC device
*/
void rtc_init() {
    outb(0x8B, 0x70);		// select register B, and disable NMI
    char prev=inb(0x71);	// read the current value of register B
    outb(0x8B, 0x70);		// set the index again (a read will reset the index to register D)
    outb(prev | 0x40, 0x71);	// write the previous value ORed with 0x40. This turns on bit 6 of register B

    outb(0x8A, 0x70);
    outb(0x06, 0x71);

    enable_irq(RTC_IRQ);
}

/* Implemntation borrowed from https://wiki.osdev.org/RTCc
    rtc_handler
    Inputs: void
    Outputs: void
    Description: handles the RTC functionality including lib.c test_interrupt call
*/
void rtc_handler () {
    outb(0x0C, 0x70);
    inb(0x71);
    
}

/**
 * Function: rtc_read
 * ------------------
 * This function, rtc_read, is responsible for reading data from a real-time clock (RTC) device.
 * It continuously checks for an interrupt signal (my_interrupt) to determine when data is available
 * for reading. The function blocks until an interrupt is received, at which point it returns 0.
 * Input
 * @param fd: File descriptor for the RTC device.
 * @param buf: A pointer to the buffer where the read data will be stored.
 * @param nbytes: The number of bytes to read from the RTC device.
 * 
 * Output: Returns 0 when data is successfully read or when an interrupt is received.
 */

int  rtc_read (int32_t fd, void* buf, int32_t nbytes) {
    my_interrupt = 0;
    while (1)
        if (my_interrupt == 1)
            break;
    return 0;
}

/**
 * Function: rtc_write
 * -------------------
 * The rtc_write function is responsible for configuring a real-time clock (RTC) device
 * to establish a specific frequency of interrupts. It writes a value from the provided buffer
 * to set the interrupt frequency. If the buffer is NULL, the function returns -1, indicating
 * error. Otherwise, it calculates the desired interrupt frequency, updates a global variable
 * (nodedu) with this frequency, and returns 0 to indicate success.
 * Input
 * @param fd: File descriptor for the RTC device.
 * @param buf: A pointer to the buffer containing the interrupt frequency value to be set.
 * @param nbytes: The number of bytes in the buffer.
 * 
 * Output: Returns 0 when the RTC is successfully configured with the desired frequency, 
 *          or -1 in case of an error, such as a NULL buffer.
 */

int rtc_write (int32_t fd, const void* buf, int32_t nbytes) {
    if (buf == NULL) {
        return -1;
    }
    uint32_t establish_freq = *((uint32_t*) buf);
    nodedu = 1024 / establish_freq;
    return 0;
}

//used osdev as a reference

/**
 * Function: frequency_updater
 * ---------------------------
 * The frequency_updater function is used to adjust the interrupt frequency of a real-time clock (RTC) device.
 * It calculates the appropriate rate based on the desired frequency in hertz and sets the RTC to generate
 * interrupts at that rate. This function ensures that the rate is within a valid range (3 to 15) before updating
 * the RTC configuration.
 * 
 * @param hertz: The desired interrupt frequency in hertz.
 * Output: void
 */
void frequency_updater (int hertz) {
    uint32_t flags;

    int rate = log2(32768.0/hertz) + 1;

    if((rate < 3) || (rate  > 15))
        return;
    cli_and_save(flags);
    outb(0x8A, 0x70);
    char prev=inb(0x71);
    outb(0x8A, 0x70);
    outb((prev & 0xF0) | rate, 0x71);
    restore_flags(flags);
}

//Name: rtc_open
//Input: const uint8_t* filename
//Output: integer, return 0 upon the end
int rtc_open (const uint8_t* filename) {
    nodedu = 1024 / 2;
    //nodedu = 1; 
    frequency_updater(2);
    return 0;
}

//Name: rtc_close
//Inputs: int32_t fd
//Output: int
int rtc_close (int32_t fd) {
    nodedu = 0;
    return 0;
}

//helper function for frequency updater
//Name: log2
//Inputs: double a
//Output: double
double log2(double a){
    if(a <= 0){
        return -1.0;
    }
    double result = 0.0;
    while (a >= 2.0){
        a /= 2.0;
        result += 1.0;
    }
    return result;
}
