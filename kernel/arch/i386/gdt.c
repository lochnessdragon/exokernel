#include "gdt.h"

#include <stdio.h>
#include <string.h>

// allows for one null descriptor, one code descriptor and one data descriptor
#define MAX_GDT_ENTRIES 3

static gdt_entry _gdt_entries[MAX_GDT_ENTRIES];
static gdt_ptr _gdt_table;

void set_gdt_entry(int index, uint32_t base, uint32_t size, uint8_t access, uint8_t flags)
{
    if (index > MAX_GDT_ENTRIES)
    {
        puts("[ ERR ] Code attempted to set a gdt entry that is higher than the max allowed!\n");
        return;
    }

    // null out the descriptor before setting any values.
    memset((void *)&_gdt_entries[index], 0, sizeof(gdt_entry));

    // initialize the base address
    // the base low address can only be 16 bits long.
    // therefore, we artifically limit it using a bitwise and operator
    // and 16 set bits.
    _gdt_entries[index].baseLow = (base & 0xffff);
    _gdt_entries[index].baseMid = ((base >> 16) & 0xff);  // can only be one byte long.
    _gdt_entries[index].baseHigh = ((base >> 24) & 0xff); // again, only one byte, but its the last byte

    // initialized the offset
    _gdt_entries[index].limitLow = (size & 0xffff);            // take the low 2 bytes of the limit (i.e. the low 16 bits)
    _gdt_entries[index].limitAndFlags = ((size >> 16) & 0x0f); // take the last half a byte

    // set up the access flags
    _gdt_entries[index].accessByte = access; // phew, thats easier.

    // set up the misc flags attached to the high limit bits
    _gdt_entries[index].limitAndFlags = (flags & 0xf0); // take the top half a byte of flags for gdt
}

void initialize_gdt()
{
    _gdt_table.address = (uint32_t)&_gdt_entries[0];
    _gdt_table.size = (sizeof(gdt_entry) * MAX_GDT_ENTRIES) - 1; // can't forget the minus 1

    // load in a null gdt entry
    set_gdt_entry(0, 0, 0, 0, 0);

    // load in a code descriptor (must have an offset of 1 for the load_code_seg function)
    set_gdt_entry(1, 0, 0xfffff, GDT_ACCESS_READWRITE | GDT_ACCESS_PRESENT | GDT_ACCESS_CODEDATA | GDT_ACCESS_EXEC_SEG, GDT_EXTRA_32BIT | GDT_EXTRA_4K_GRANULARITY);

    // load in a data descriptor (fill the entire address space)
    set_gdt_entry(2, 0, 0xfffff, GDT_ACCESS_READWRITE | GDT_ACCESS_PRESENT | GDT_ACCESS_CODEDATA, GDT_EXTRA_32BIT | GDT_EXTRA_4K_GRANULARITY);

    // finally, load the gdt into the gdtr
    load_gdtr(_gdt_table);

    // load in the correct segment for data descriptors
    load_data_segs(2 * sizeof(gdt_entry));
    // farjump to fix cs
    load_code_seg();
}