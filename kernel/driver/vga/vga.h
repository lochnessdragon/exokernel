#pragma once

void vga_write(const char* string, int len);
void vga_set_cell(char c, char attrib_byte);
void vga_append_char(char c);

void vga_hardware_cursor(unsigned char x, unsigned char y);