#include "vga.h"

#define VGA_MEM 0xB8000
#define COLS 80
#define LINES 25

#define TEXT_ATTRIB 0x07

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
}