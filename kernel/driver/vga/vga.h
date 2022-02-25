#pragma once

#include <stdint.h>

void vga_write(const char* string, int len);
void vga_set_cell(int x, int y, char c, char attrib_byte);
uint16_t vga_get_cell(int x, int y);
void vga_append_char(char c);

void vga_hardware_cursor(unsigned char x, unsigned char y);
void vga_scroll();