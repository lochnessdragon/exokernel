#ifndef _IDT_H
#define _IDT_H

#include <stdint.h>
#include <common/packed_struct.h>

#define MAX_INTERRUPTS 256

// interrupt flags/helper defines

#define INTERRUPT_DEFAULT_CS (1 << 3)// 0x8 is the default code selector (i.e. kernel)

// flags
// 1000 0000
#define INTERRUPT_PRESENT (1 << 7)

// 0110 0000
#define INTERRUPT_DPL_RING3 (3 << 5)
// 0010 0000
#define INTERRUPT_DPL_RING2 (1 << 5)
// 0100 0000
#define INTERRUPT_DPL_RING1 (1 << 6)

// 0000 1110
#define INTERRUPT_32BIT (7 << 1)

// an interrupt entry.
// The bits are as follows:
// Highest:
// Bit:     | 31              16 | 15 | 14 13 | 12 | 11 | 10 9 8 | 7 6 5 | 4 3 2 1 0 |
// Content: | offset high        | P  | DPL   | 0  | D  | 1  1 0 | 0 0 0 | reserved  |
// Lowest:
// Bit:     | 31              16 | 15              0 |
// Content: | segment selector   | offset low        |
typedef struct idt_entry {
    uint16_t offsetLow;
    uint16_t segmentSel;
    uint8_t reserved; // must be 0
    uint8_t flags; // includes present flag, priveledge level flag and gate type flag
    uint16_t offsetHigh;
} packed_struct idt_entry;

// the idtr is the exact same as the gdtr, however, I guess we will repeat the structure for brevity

typedef struct idt_ptr {
    uint16_t size;
    uint32_t address;
} packed_struct idt_ptr;

_Static_assert(sizeof(idt_entry) == 8, "The idt_entry must be 8 bytes in length!");
_Static_assert(sizeof(idt_ptr) == 6, "The idt_ptr must be 6 bytes in length!");

// interrupt function macro (expands to compiler specific builtins to enable interrupts)
#ifdef __GNUC__

struct interrupt_frame {
    unsigned int eip;
    unsigned int cs;
    unsigned int eflags;
} packed_struct;

#define INTERRUPT __attribute__((interrupt))
#else 
#error GCC must be used to compile the exokernel!
#endif

#ifdef __x86_64__
typedef unsigned long long int uword_t;
#else
typedef unsigned int uword_t;
#endif

typedef INTERRUPT void (*irq_handler)(struct interrupt_frame*);
typedef INTERRUPT void (*irq_error_handler)(struct interrupt_frame*, uword_t error_code);

void initialize_interrupts();
int install_interrupt(uint32_t index, uint16_t flags, uint16_t selector, irq_handler handler_func);

// asm subroutinues
extern void enable_interrupts();
extern void disable_interrupts();
extern void load_idtr(idt_ptr ptr);
void gen_interrupt(int interrupt_number);

#endif // _IDT_H