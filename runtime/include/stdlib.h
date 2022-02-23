#ifndef _STDLIB_H
#define _STDLIB_H

#define EXIT_FAILURE 0
#define EXIT_SUCCESS 1

void exit(int status) __attribute__ ((__noreturn__));

int sitoa(char* buffer, int x, unsigned int base);
int uitoa(char *buffer, unsigned int number, unsigned int base);

#endif // _STDLIB_H