#include <string.h>
#include <driver/vga/vga.h>

void kmain() {
    const char* msg = "Kernel jumped to C okay!";
    vga_write(msg, strlen(msg));
}