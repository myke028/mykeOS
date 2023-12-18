/* exceptions.S */

/* Import the C functions */
.extern FAULT_divide_error
.extern FAULT_TRAP_reserved
.extern INTERRUPT_nmi
.extern TRAP_breakpoint
.extern TRAP_overflow
.extern FAULT_bound_range_exceeded
.extern FAULT_invalid_opcode
.extern FAULT_device_not_available
.extern ABORT_double_fault
.extern FAULT_coproccessor_segment_overrun
.extern FAULT_invalid_tss
.extern FAULT_segment_not_present
.extern FAULT_stack_segment
.extern FAULT_general_protection
.extern FAULT_page
// extern reserved
.extern FAULT_math
.extern FAULT_alignment_check
.extern ABORT_machine_check
.extern FAULT_simd_floating_point_exception

.section .text
.global exception_handler

exception_handler:
    /* Your exception handler code goes here */
    /* For example, you might want to print an error message or handle the exception in some way */

    /* Call the corresponding C function */
    pushl %eax
    movl %esp, %eax
    pushl %eax
    call *%ecx   /* %ecx contains the address of the C function */
    popl %eax
    popl %eax
    iret

/* Repeat the above for each exception */

/* Add more sections if necessary (e.g., for data) */