/* i8259.c - Functions to interact with the 8259 interrupt controller
 * vim:ts=4 noexpandtab
 */

#include "i8259.h"



/*  definitions below from https://wiki.osdev.org/PIC  */
////////////////////////////////////////////////////////////////////////////////
#define PIC1		0x20		/* IO base address for master PIC */
#define PIC2		0xA0		/* IO base address for slave PIC */
#define PIC1_COMMAND	PIC1
#define PIC1_DATA	(PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA	(PIC2+1)

/* reinitialize the PIC controllers, giving them specified vector offsets
   rather than 8h and 70h, as configured by default */
 
#define ICW1_ICW4	0x01		/* Indicates that ICW4 will be present */
#define ICW1_SINGLE	0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL	0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	0x10		/* Initialization - required! */
 
#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
#define ICW4_SFNM	0x10		/* Special fully nested (not) */

////////////////////////////////////////////////////////////////////////////////

#define PARENT 0x20 // osdev: parent/master is OFFSET1
#define CHILD 0x28 //child is OFFSET2

#define MASK 0xFF

// PIC ports
#define PARENT_COMMAND_REG 0x20
#define PARENT_IMR_REG 0x21
#define CHILD_COMMAND_REG 0xA0
#define CHILD_IMR_REG 0xA1



/* Interrupt masks to determine which interrupts are enabled and disabled */
uint8_t parent_mask; /* IRQs 0-7  */
uint8_t child_mask;  /* IRQs 8-15 */

/* Initialize the 8259 PIC 
    Inputs: void
    Return: void
    Description: Initializes the PIC with parent/child
*/
void i8259_init(void) { //parts of initialization implementation from osdev: https://wiki.osdev.org/PIC
    
    parent_mask = MASK;
    child_mask = MASK;

 
    outb(MASK, PARENT_IMR_REG);
    outb(MASK, CHILD_IMR_REG);

	outb(ICW1, PARENT_COMMAND_REG);  // starts the initialization sequence (in cascade mode)

    outb(ICW1, CHILD_COMMAND_REG);

    outb(PARENT, PARENT_IMR_REG);                 // ICW2: Master PIC vector offset

    outb(CHILD, CHILD_IMR_REG);                 // ICW2: Slave PIC vector offset

    outb(ICW3_MASTER /*4*/, PARENT_IMR_REG);                       // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)

    outb(ICW3_SLAVE /*2*/, CHILD_IMR_REG);                       // ICW3: tell Slave PIC its cascade identity (0000 0010)


    outb(ICW4_8086, PARENT_IMR_REG);               // ICW4: have the PICs use 8086 mode (and not 8080 mode)

    outb(ICW4_8086, CHILD_IMR_REG);


    outb(parent_mask, PARENT_IMR_REG);   // restore saved masks.
    outb(child_mask, CHILD_IMR_REG);

    enable_irq(2);
}

/* Enable (unmask) the specified IRQ 
    Inputs: irq_num - designated Interrupt Request Number of given device
    Outputs: void
    Description: 
*/
void enable_irq(uint32_t irq_num) {
    
    if (irq_num >= 2 * 8 /*I8259_PORTS_NUMBER*/){
        return;
    }
    
    if (irq_num >= 8){
        child_mask &= ~(1 << (irq_num - 8));
        outb(child_mask, CHILD_IMR_REG);
    }
    
    else{
        parent_mask &= ~(1 << irq_num);
        outb(parent_mask, PARENT_IMR_REG);
    }

}

/* Disable (mask) the specified IRQ */
void disable_irq(uint32_t irq_num) {

    if (irq_num >= 2 * 8){
        return;
    }
    
    if (irq_num >= 8){
        child_mask |= (1 << (irq_num - 8));
        outb(child_mask, CHILD_IMR_REG);
    }
    
    else{
        parent_mask |= (1 << irq_num);
        outb(parent_mask, PARENT_IMR_REG);
    }
}

/* Send end-of-interrupt signal for the specified IRQ */
void send_eoi(uint32_t irq_num) {

    if (irq_num >= 2 * 8){return;}
    
    if (irq_num >= 8){
        outb(EOI | (irq_num - 8), CHILD_COMMAND_REG);
        outb(EOI | 2 /*master slave pin*/, PARENT_COMMAND_REG);
    }
    else {
        outb(EOI | irq_num, PARENT_COMMAND_REG);
    }
}
