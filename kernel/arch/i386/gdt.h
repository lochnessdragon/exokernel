#ifndef _GDT_H
#define _GDT_H
#include <common/packed_struct.h>
#include <stdint.h>

/**
 * @brief gdt_entry describes an entry in the global descriptor table
 * This should always only be 8-bytes in length.
 * see: https://wiki.osdev.org/Global_Descriptor_Table
 */
typedef struct gdt_entry {
    uint16_t limitLow;
    uint16_t baseLow;
    uint8_t baseMid;
    uint8_t accessByte;
    uint8_t limitAndFlags;
    uint8_t baseHigh;
} packed_struct gdt_entry;

typedef struct gdt_ptr {
    uint16_t size;
    uint32_t address;
} packed_struct gdt_ptr;

// size protections
_Static_assert (sizeof(gdt_entry)==8, "All gdt entries need to be 8 bytes long.");
_Static_assert (sizeof(gdt_ptr)==6, "The gdt pointer must be 6 bytes in length.");

// GDT entry flag defines (to toggle flags for the access byte and miscellaneous flags)
// GDT Access Flags
// 10000000
#define GDT_ACCESS_PRESENT 0x0080 // must be on for any valid entry. says that this segment is in memory

// 01100000
#define GDT_ACCESS_DPL_RING3 0x0060 // the privledge level of this segment (normally kernel i.e. 0)

// 00010000
#define GDT_ACCESS_CODEDATA 0x0010 // sets the bit to indicate this segment is a code or data segment

// 00001000
#define GDT_ACCESS_EXEC_SEG 0x0008 // sets the bit to indicate that this is a code segment, not a data segment

// 00000100
#define GDT_ACCESS_EXPANSION 0x0004 // controls the direction that data segments are defined in
// and whether code segments are restricted to being controlled by only the ring specified in the DPL

// 00000010
#define GDT_ACCESS_READWRITE 0x0002 // enables reading code segments or writing to data segments

// 00000001
#define GDT_ACCESS_SEG_IS_ACCESSED 0x0001 // set when the cpu detects that a segment is being accessed

// GDT Miscellaneous Flags (attached to the upper bits of the size)
// 10000000
#define GDT_EXTRA_4K_GRANULARITY 0x80 // set when the size should be multiplied by 4 kilobytes (i.e. the largest size with this flag is 4GB, the limit of the addressable memory)

// 01000000
#define GDT_EXTRA_32BIT 0x40 // use this flag to indicate that the segment should be using 32 bit code. the default is 16-bit
/**
 * Note: Yes, theroetically, the last flag byte can be controlled by the os.
 * However, wiki.osdev.org marks that flag as reserved, so we will not include that definition
 * here.
 */

void initialize_gdt();
void set_gdt_entry(int index, uint32_t base, uint32_t size, uint8_t access, uint8_t flags);

// asssembly subroutinues
extern void load_gdtr(gdt_ptr ptr);

// note for the next function, multiply the index of the segment by 8 to get the offset.
extern void load_data_segs(uint16_t offset);

// this function loads the code segment as the first segment after the null segment
// if someone can get it to take arbitrary offsets, that would be great
// but idk how to do that.
extern void load_code_seg();

#endif // _GDT_H