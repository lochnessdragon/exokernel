#include "vga.h"
#include <arch/i386/ports.h>

#define VGA_MEM 0xB8000
#define COLS 80
#define LINES 25

#define TEXT_ATTRIB 0x07

/* The I/O ports */
#define FB_COMMAND_PORT         0x3D4
#define FB_DATA_PORT            0x3D5

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15

char* fb = (char*)VGA_MEM;

unsigned char cursor_x = 0;
unsigned char cursor_y = 0;

void vga_write_cell(char c, char attrib_byte) {
    int offset = (cursor_x*2) + (cursor_y * COLS * 2);

    fb[offset] = c;
    fb[offset+1] = attrib_byte;
}

void vga_write(const char* string, int len) {
    // write to the vga
    for(int i = 0; i < len; i++) {
        if(string[i] == '\n') {
            cursor_x = 0;
            cursor_y++;
            continue;
        }

        if(cursor_y >= LINES) {
			cursor_y = 0;
		}

		vga_write_cell (string[i], TEXT_ATTRIB);
		cursor_x++;
		if(cursor_x >= COLS) {
			cursor_x = 0;
			cursor_y++;
		}

    }

    vga_hardware_cursor(cursor_x, cursor_y);
}

void vga_hardware_cursor(unsigned char x, unsigned char y) {
    cursor_x = x;
    cursor_y = y;

    unsigned short pos = cursor_x + (cursor_y * COLS);

    outportb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outportb(FB_DATA_PORT,    ((pos >> 8) & 0x00FF));
    outportb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outportb(FB_DATA_PORT,    pos & 0x00FF);
}