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

void vga_set_cell(int x, int y, char c, char attrib_byte) {
    int offset = (x*2) + (y * COLS * 2);

    fb[offset] = c;
    fb[offset+1] = attrib_byte;
}

uint16_t vga_get_cell(int x, int y) {
	int offset = (x * 2) + (y * COLS * 2);

	return (fb[offset] << 8) | fb[offset+1];
}

void vga_append_char(char c) {
    if(c == '\n') {
        cursor_x = 0;
        cursor_y++;
        return;
    }

    if(cursor_y >= LINES) {
			vga_scroll();
		cursor_y -= 1;
	}

	vga_set_cell (cursor_x, cursor_y, c, TEXT_ATTRIB);
	cursor_x++;
	if(cursor_x >= COLS) {
		cursor_x = 0;
		cursor_y++;
	}

    vga_hardware_cursor(cursor_x, cursor_y);
}

void vga_write(const char* string, int len) {
    // write to the vga
    for(int i = 0; i < len; i++) {
        vga_append_char(string[i]);
    }
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

void vga_scroll() {
	for(int y = 0; y < LINES-1; y++) {
		for(int x = 0; x < COLS; x++) {
			uint32_t replacement = vga_get_cell(x, y+1);
			vga_set_cell(x, y, (char) ((replacement >> 8) & 0x00ff), (char) (replacement & 0x00ff));
		}
	}
	// null out the last line
	for(int x = 0; x < COLS; x++) {
		vga_set_cell(x, LINES - 1, 0, TEXT_ATTRIB);
	}
}