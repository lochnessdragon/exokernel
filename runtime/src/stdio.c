#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

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

int printint(int x, unsigned int base) {
    char buffer[20] = {0};
    int str_len = sitoa(buffer, x, base);
    for(int i = 0; i < str_len; i++) {
        putchar(buffer[i]);
    }

    return str_len;
}

int printuint(unsigned int x, unsigned int base) {
    char buffer[20] = {0};
    int str_len = uitoa(buffer, x, base);
    for(int i = 0; i < str_len; i++) {
        putchar(buffer[i]);
    }

    return str_len;
}

int printf(const char* restrict fmt, ...) {
    int count = 0;
    va_list args;
    va_start(args, fmt);

    char c = '0';

    while((c = *fmt++) != 0) {
        if(c != '%') {
            count++;
            putchar(c);
        } else {
            c = *fmt++;
            char* str_buf;

            switch(c) {
                case '%':
                    count++;
                    putchar('%');
                    break;
                case 'd':
                case 'i':
                    count += printint(va_arg(args, int), 10);
                    break;
                case 'o':
                    count += printuint(va_arg(args, unsigned int), 8);
                    break;
                case 'u':
                    count += printuint(va_arg(args, unsigned int), 10);
                    break;
                case 'x':
                case 'X':
                    count += printuint(va_arg(args, unsigned int), 16);
                    break;
                case 's':
                    str_buf = va_arg(args, char*);

                    if(!str_buf)
                        str_buf = "(null)";

                    for(;*str_buf; str_buf++) {
                        count++;
                        putchar(*str_buf);
                    }

                    break;
                default:
                    break;
            }
        }
    }

    va_end(args);
    return count;
}