#include <string.h>
#include <driver/vga/vga.h>

void kmain() {
    const char* msg = "Kernel jumped to C okay!\n";
    vga_write(msg, strlen(msg));

    // now we have to get to x86_64...
}