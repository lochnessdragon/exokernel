#include "vga.h"

void vga_write(const char* string, int len) {
    // write to the vga
    for(int i = 0; i < len; i++) {
        char c = *(string + i);
        c++;
    }
}