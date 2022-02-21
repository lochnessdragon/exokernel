#include <stdio.h>
#include <string.h>

#ifdef __kernel_libk
#include <driver/vga/vga.h>
#endif

int putchar(int c) {
    #ifdef __kernel_libk
    vga_append_char(c);
    #else 
    #error This runtime library function doesnt work outside of a kernel environment
    #endif
    return 1;
}

int puts(const char *s) {
    int len = strlen(s);
    for(int i = 0; i < len; i++) {
        putchar(s[i]);
    }

    putchar('\n');
    return 1;
}