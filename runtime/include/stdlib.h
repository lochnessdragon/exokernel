#ifndef _STDLIB_H
#define _STDLIB_H

#define EXIT_FAILURE 0
#define EXIT_SUCCESS 1

#include <stdbool.h>

void exit(int status) __attribute__ ((__noreturn__));

// 7.22.6 - Integer arithmetic functions
// 7.22.6.1 - abs, labs, llabs
int abs(int x);
long int labs(long int x);
long long int llabs(long long int x);

int itoa(char* buffer, int x, unsigned int base, bool isSigned);

#endif // _STDLIB_H