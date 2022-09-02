#include <string.h>
#include <stdio.h>
#include <driver/vga/vga.h>
#include "gdt.h"
#include <common/multiboot2.h>
#include "compat_checks.h"
#include <driver/serial/serial.h>
#include "idt.h"
#include "common_exceptions.h"

void kmain(unsigned long multiboot_addr, unsigned int magic)
{
    struct multiboot_tag *tag;
    uint32_t multiboot_size;
    initialize_serial();
		clear_vga();

		// check if we were loaded by a multiboot compliant bootloader.
    if (magic != MULTIBOOT2_BOOTLOADER_MAGIC)
    {
        puts("[ ERR ] The kernel must be loaded by a multiboot2 complaint bootloader!");
        return;
    }

    // check for things like long mode, PAE, MMX and SSE
    if(!processor_is_supported()) return;
	
    // extract relevant info from the multiboot header
    multiboot_size = *((uint32_t *)multiboot_addr);
    printf("Multiboot size is: 0x%x bytes\n", multiboot_size);
    for (tag = (struct multiboot_tag *)(multiboot_addr + 8); tag->type != MULTIBOOT_TAG_TYPE_END; tag = (struct multiboot_tag *)((multiboot_uint8_t *)tag + ((tag->size + 7) & ~7)))
    {
        //printf("Tag: 0x%x, Size 0x%x\n", tag->type, tag->size);

        switch (tag->type)
        {
        case MULTIBOOT_TAG_TYPE_CMDLINE:;
            struct multiboot_tag_string *cmdline = (struct multiboot_tag_string *)tag;
            printf("Command line: %s \n", cmdline->string);
            break;
        case MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME:;
            struct multiboot_tag_string *boot_name = (struct multiboot_tag_string *)tag;
            printf("Bootloader name: %s \n", boot_name->string);
            break;
        case MULTIBOOT_TAG_TYPE_BASIC_MEMINFO:;
            struct multiboot_tag_basic_meminfo *meminfo = (struct multiboot_tag_basic_meminfo *)tag;
            printf("Memory: mem_lower=%uKB, mem_upper=%uKB\n", meminfo->mem_lower, meminfo->mem_upper);
            break;
        case MULTIBOOT_TAG_TYPE_BOOTDEV:;
            struct multiboot_tag_bootdev *bootdev = (struct multiboot_tag_bootdev *)tag;
            printf("Boot device: 0x%x, %u, %u\n", bootdev->biosdev, bootdev->slice, bootdev->part);
            break;
        case MULTIBOOT_TAG_TYPE_MMAP:;
            struct multiboot_tag_mmap *mmap_tag = (struct multiboot_tag_mmap *)tag;
            multiboot_memory_map_t *memorymap;
						printf("Memmap:\n");
            for (memorymap = mmap_tag->entries; (uint8_t *)memorymap < ((uint8_t *)tag + tag->size); memorymap = (multiboot_memory_map_t *)((unsigned long)memorymap + mmap_tag->entry_size))
            {
                printf (" base_addr = 0x%x%x,"
                      " length = 0x%x%x, type = 0x%x\n",
                      (unsigned) (memorymap->addr >> 32),
                      (unsigned) (memorymap->addr & 0xffffffff),
                      (unsigned) (memorymap->len >> 32),
                      (unsigned) (memorymap->len & 0xffffffff),
                      (unsigned) memorymap->type);
            }
            break;
        case MULTIBOOT_TAG_TYPE_NETWORK:;
            struct multiboot_tag_network* network = (struct multiboot_tag_network*) tag;
            printf("Network DHCP: %d\n", network->dhcpack);
            break;
        case MULTIBOOT_TAG_TYPE_APM:;
            struct multiboot_tag_apm* apm = (struct multiboot_tag_apm*) tag;
            printf("APM: version = 0x%x\n", apm->version);
            break;
        case MULTIBOOT_TAG_TYPE_LOAD_BASE_ADDR:;
            struct multiboot_tag_load_base_addr* base_addr = (struct multiboot_tag_load_base_addr*) tag;
            printf("Base address load: 0x%x\n", base_addr->load_base_addr);
            break;
        case MULTIBOOT_TAG_TYPE_FRAMEBUFFER:;
            struct multiboot_tag_framebuffer* framebuffer = (struct multiboot_tag_framebuffer*) tag;
            printf("Framebuffer: width = %d height = %d\n", framebuffer->common.framebuffer_width, framebuffer->common.framebuffer_height);
            break;
        case MULTIBOOT_TAG_TYPE_ELF_SECTIONS:;
            struct multiboot_tag_elf_sections* elf_sections = (struct multiboot_tag_elf_sections*) tag;
            printf("Elf sections: number = %d entry size = %d shndx = %d\n", elf_sections->num, elf_sections->num, elf_sections->shndx);
            break;
        default:
            break;
        }
    }

    // now we have to get to x86_64...

    // setup a basic gdt
    initialize_gdt();
    puts("[ OK ] Initial x86 GDT setup!");

    // initialize interrupts
    initialize_interrupts();

    // add exception vectors
    install_exception_handlers();

    // initialize the PIC and PIT

    enable_interrupts();
    puts("[ OK ] Initialized x86 interrupts!");

    // set up x64 gdt and idt
    // initialize x64 TSS
    // initialize x64 4 level paging (but do not enable)
    // enable PAE
    // load CR3
    // enable long mode
    // enable paging and jump into long mode w/ compatibility mode on!
    // switch into totally x64

    // jump to the kernel
}