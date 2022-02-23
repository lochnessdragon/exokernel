#include <string.h>
#include <stdio.h>
#include <driver/vga/vga.h>
#include "gdt.h"
#include <common/multiboot2.h>

void kmain(unsigned long multiboot_addr, unsigned int magic)
{
    struct multiboot_tag *tag;
    uint32_t multiboot_size;

    puts("[ OK ] Kernel jumped to C okay!");

    if (magic != MULTIBOOT2_BOOTLOADER_MAGIC)
    {
        puts("[ ERR ] The kernel must be loaded by a multiboot2 complaint bootloader!");
        return;
    }

    // extract relevant info from the multiboot header
    multiboot_size = *((uint32_t *)multiboot_addr);
    printf("Multiboot size is: 0x%x bytes\n", multiboot_size);
    for (tag = (struct multiboot_tag *)(multiboot_addr + 8); tag->type != MULTIBOOT_TAG_TYPE_END; tag = (struct multiboot_tag *)((multiboot_uint8_t *)tag + ((tag->size + 7) & ~7)))
    {

    }

    // now we have to get to x86_64...

    // setup a basic gdt
    initialize_gdt();
    puts("[ OK ] Initial x86 GDT setup!");

    // initialize interrupts
    puts("[ OK ] Initial interrupt routinues setup!");

    // initialize the PIC and PIT

    // initialize memory paging

    // load the kernel

    // switch into x86_64

    // jump to the kernel
}