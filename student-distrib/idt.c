#include "x86_desc.h"
#include "lib.h"
#include "keyboard.h"
#include "interrupt.h"


static char* exception_names[] = {
    "FAULT_divide_error",
    "FAULT_TRAP_reserved", // reserved?
    "INTERRUPT_nmi",
    "TRAP_breakpoint",
    "TRAP_overflow",
    "FAULT_bound_range_exceeded",
    "FAULT_invalid_opcode",
    "FAULT_device_not_available",
    "ABORT_double_fault",
    "FAULT_coproccessor_segment_overrun", 
    "FAULT_invalid_tss",
    "FAULT_segment_not_present",
    "FAULT_stack_segment",
    "FAULT_general_protection",
    "FAULT_page",
    // "reserved", // 15 reserved
    "FAULT_math",
    "FAULT_alignment_check",
    "ABORT_machine_check",
    "FAULT_simd_floating_point_exception",
};


/* exception_log
    Inputs: vector_no - the index of the exception vector
    Outputs: void
    Description: 
*/
void exception_log(int vector_no){
    cli();
    printf("\n!!! Exception Found !!!\n");
    printf("Exception Vector No. %d: %s\n\n\n", vector_no, exception_names[vector_no]);
    while(1){}
}

void FAULT_divide_error(){
    exception_log(0);    
}
void FAULT_TRAP_reserved(){
    exception_log(1);    
}
void INTERRUPT_nmi(){
    exception_log(2);    
}
void TRAP_breakpoint(){
    exception_log(3);    
}
void TRAP_overflow(){
    exception_log(4);    
}
void FAULT_bound_range_exceeded(){
    exception_log(5);    
}
void FAULT_invalid_opcode(){
    exception_log(6);    
}
void FAULT_device_not_available(){
    exception_log(7);    
}
void ABORT_double_fault(){
    exception_log(8);    
}
void FAULT_coproccessor_segment_overrun(){
    exception_log(9);    
}
void FAULT_invalid_tss(){
    exception_log(10);    
}
void FAULT_segment_not_present(){
    exception_log(11);    
}
void FAULT_stack_segment(){
    exception_log(12);    
}
void FAULT_general_protection(){
    exception_log(13);    
}
void FAULT_page(){
    exception_log(14);    
}
void FAULT_math(){
    exception_log(16);    
}
void FAULT_alignment_check(){
    exception_log(17);    
}
void ABORT_machine_check(){
    exception_log(18);    
}
void FAULT_simd_floating_point_exception(){
    exception_log(19);    
}



void idt_init() {
    int i = 0;
    for(i = 0; i < NUM_VEC; i++) {
        if( i < 20) {
            if(i== 15){ //15 is reserved
                continue;
            }
            idt[i].present = 1;
            idt[i].seg_selector = KERNEL_CS;
            idt[i].reserved0 = 0;
            idt[i].reserved1 = 1;
            idt[i].reserved2 = 1;
            idt[i].reserved3 = 0;
            idt[i].reserved4 = 0;
            idt[i].size = 1;
            idt[i].dpl = 0;
        }
       
    }

    SET_IDT_ENTRY(idt[0], FAULT_divide_error);
    SET_IDT_ENTRY(idt[1], FAULT_TRAP_reserved); // ?
    SET_IDT_ENTRY(idt[2], INTERRUPT_nmi);
    SET_IDT_ENTRY(idt[3], TRAP_breakpoint);
    SET_IDT_ENTRY(idt[4], TRAP_overflow);
    SET_IDT_ENTRY(idt[5], FAULT_bound_range_exceeded);
    SET_IDT_ENTRY(idt[6], FAULT_invalid_opcode);
    SET_IDT_ENTRY(idt[7], FAULT_device_not_available);
    SET_IDT_ENTRY(idt[8], ABORT_double_fault);
    SET_IDT_ENTRY(idt[9], FAULT_coproccessor_segment_overrun);
    SET_IDT_ENTRY(idt[10], FAULT_invalid_tss);
    SET_IDT_ENTRY(idt[11], FAULT_segment_not_present);
    SET_IDT_ENTRY(idt[12], FAULT_stack_segment);
    SET_IDT_ENTRY(idt[13], FAULT_general_protection);
    SET_IDT_ENTRY(idt[14], FAULT_page);
    //SET_IDT_ENTRY(idt[15], );         //15 reserved
    SET_IDT_ENTRY(idt[16], FAULT_math);
    SET_IDT_ENTRY(idt[17], FAULT_alignment_check);
    SET_IDT_ENTRY(idt[18], ABORT_machine_check);
    SET_IDT_ENTRY(idt[19], FAULT_simd_floating_point_exception);



    //hardware interrupts
    SET_IDT_ENTRY(idt[0x28], rtc_interrupt);
    idt[0x28].present = 1;
    idt[0x28].seg_selector = KERNEL_CS;
    idt[0x28].reserved0 = 0;
    idt[0x28].reserved1 = 1;
    idt[0x28].reserved2 = 1;
    idt[0x28].reserved3 = 0;
    idt[0x28].reserved4 = 0;
    idt[0x28].size = 1;
    SET_IDT_ENTRY(idt[0x21], keyboard_interrupt);
    idt[0x21].present = 1;
    idt[0x21].seg_selector = KERNEL_CS;
    idt[0x21].reserved0 = 0;
    idt[0x21].reserved1 = 1;
    idt[0x21].reserved2 = 1;
    idt[0x21].reserved3 = 0;
    idt[0x21].reserved4 = 0;
    idt[0x21].size = 1;




}

