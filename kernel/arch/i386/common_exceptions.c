#include <common_exceptions.h>

#include <stdio.h>

// 0 - Divide by zero error
INTERRUPT void divide_by_zero(struct interrupt_frame* frame) {
    printf("Divide by zero error: ip=0x%x\n", frame->eip);
}

// 1
INTERRUPT void debug_interrupt(struct interrupt_frame* frame) {
    printf("Debug interrupt called. ip=0x%x\n", frame->eip);
}

// 2
INTERRUPT void non_maskable_interrupt(struct interrupt_frame* frame) {
    printf("NMI interrupt called: ip=0x%x\n", frame->eip);
}

// 3
INTERRUPT void breakpoint_interrupt(struct interrupt_frame* frame) {
    printf("Breakpoint interrupt called: ip=0x%x\n", frame->eip);
}

// 4
INTERRUPT void overflow_interrupt(struct interrupt_frame* frame) {
    printf("Overflow interrupt called: ip=0x%x\n", frame->eip);
}

void install_exception_handlers() {
    install_interrupt(0, INTERRUPT_32BIT | INTERRUPT_PRESENT, INTERRUPT_DEFAULT_CS, divide_by_zero);
    install_interrupt(1, INTERRUPT_32BIT | INTERRUPT_PRESENT, INTERRUPT_DEFAULT_CS, debug_interrupt);
    install_interrupt(2, INTERRUPT_32BIT | INTERRUPT_PRESENT, INTERRUPT_DEFAULT_CS, non_maskable_interrupt);
    install_interrupt(3, INTERRUPT_32BIT | INTERRUPT_PRESENT, INTERRUPT_DEFAULT_CS, breakpoint_interrupt);
    install_interrupt(4, INTERRUPT_32BIT | INTERRUPT_PRESENT, INTERRUPT_DEFAULT_CS, overflow_interrupt);
}