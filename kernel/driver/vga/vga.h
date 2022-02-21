#pragma once

void vga_write(const char* string, int len);
void vga_write_cell(char c, char attrib_byte);