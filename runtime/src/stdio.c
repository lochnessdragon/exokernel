#include <stdio.h>
#include <string.h>

#ifdef __kernel_libk
#include <driver/vga/vga.h>
#else
#include <unistd.h>
#endif
// define stdio
#ifndef __kernel_libk
FILE __STDIN__ = {
	0
};
FILE __STDOUT__ = {
	1
};
FILE __STDERR__ = {
	2
};

FILE* __STDIN=&__STDIN__;
FILE* __STDOUT=&__STDOUT__;
FILE* __STDERR=&__STDERR__;
#endif

// file operations functions
#ifndef __kernel_libk
int remove(const char* filename) {
	return unlink(filename);
}
#endif

int putchar(int c) {
    #ifdef __kernel_libk
    vga_append_char(c);
    #else 
    write((*stdout).fd, &c, 1);
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