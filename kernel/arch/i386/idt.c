#include "idt.h"
#include <string.h>
#include <stdio.h>

static idt_ptr _idtr;
static idt_entry _idt_table[MAX_INTERRUPTS];

// default interrupt handler to catch unhandled interrupts
INTERRUPT static void default_interrupt_handler(struct interrupt_frame* frame) {

    printf("[ ERR ]: Default interrupt handler called cs=0x%x eip=0x%x eflags=0x%x!", frame->cs, frame->eip, frame->eflags);
}

int install_interrupt(uint32_t index, uint16_t flags, uint16_t selector, irq_handler handler_func) {
    if(index > MAX_INTERRUPTS)
        return 0;
    
    if(!handler_func) 
        return 0;
    
    uint32_t interrupt_ptr = (uint32_t) handler_func;
    _idt_table[index].offsetLow = (uint16_t) (interrupt_ptr & 0xffff);
    _idt_table[index].offsetLow = (uint16_t) ((interrupt_ptr >> 16) & 0xffff);
    _idt_table[index].reserved = 0;
    _idt_table[index].flags = flags;
    _idt_table[index].segmentSel = selector;

    return 0;
}

void initialize_interrupts() {
    // initialize the idtr with infomation about the idt table
    puts("Setting idtr");
    _idtr.address = (uint32_t) _idt_table;
    _idtr.size = sizeof(idt_entry) * MAX_INTERRUPTS - 1; // dont forget -1

    // null out the idt
    puts("Nulling idt");
    memset(_idt_table, 0, sizeof(idt_entry) * MAX_INTERRUPTS - 1);

    // register the default handlers
    puts("Registering default handlers");
    for(int i = 0; i < MAX_INTERRUPTS; i++) {
        install_interrupt(i, INTERRUPT_32BIT | INTERRUPT_PRESENT, INTERRUPT_DEFAULT_CS, (irq_handler)default_interrupt_handler);
    }

    // load interrupts
    puts("Loading idtr");
    load_idtr(_idtr);

    // enable interrupts
    puts("Enabling interrupts!");
    enable_interrupts();
}