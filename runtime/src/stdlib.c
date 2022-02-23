#include <stdlib.h>

#ifndef __kernel_libk
#include <unistd.h>
#endif
#ifndef __kernel_libk
void exit(int status) {
    _exit(status);
}
#endif

int sitoa(char* buffer, int x, unsigned int base) {
    char symbols[] = "0123456789abcdef";
    if (base >= sizeof(symbols) || base <= 1) return -1;

    char *buffer_start = buffer;
    int is_positive = x >= 0;
    // absolute value, unsigned because -INT_MIN is ub 
    //unsigned int number_a = is_positive ? (unsigned int)x : -((unsigned int)x); 

    // always do the first digit, so that zero is not the empty string
    do
    {
        *buffer = symbols[x % base];
        x /= base;
        buffer++;
    } while (x); 

    *buffer = '-'; // this will be overwritten by the null if the number is positive
    buffer -= is_positive;
    int length = (int)(buffer - buffer_start + 1);
    buffer[1] = '\0';
    
    // reverse the string (leaving the null in place)
    while (buffer > buffer_start)
    {
        char temp = *buffer_start;
        *(buffer_start++) = *buffer;
        *(buffer--) = temp;
    }

    return length;
}

int uitoa(char *buffer, unsigned int number, unsigned int base)
{
    char symbols[] = "0123456789abcdef";
    if (base >= sizeof(symbols) || base <= 1) return -1;

    char *buffer_start = buffer;
    
    // always do the first digit, so that zero is not the empty string
    do
    {
        *buffer = symbols[number % base];
        number /= base;
        buffer++;
    } while (number); 

    int length = (int)(buffer - buffer_start);
    *buffer = '\0';
    buffer--;

    // reverse the string (leaving the null in place)
    while (buffer > buffer_start)
    {
        char temp = *buffer_start;
        *(buffer_start++) = *buffer;
        *(buffer--) = temp;
    }

    return length;
}