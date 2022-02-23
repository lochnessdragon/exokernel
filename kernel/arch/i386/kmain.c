#include <string.h>
#include <stdio.h>
#include <driver/vga/vga.h>
#include "gdt.h"

void kmain() {
    puts("[ OK ] Kernel jumped to C okay!");
    // now we have to get to x86_64...

    // setup a basic gdt
    initialize_gdt();
    puts("[ OK ] Initial x86 GDT setup!");

    // initialize interrupts

    // initialize the PIC and PIT

    // initialize memory paging

    // load the kernel

    // switch into x86_64

    // jump to the kernel
}