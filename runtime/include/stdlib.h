#ifndef _STDLIB_H
#define _STDLIB_H

#include "null.h"

#define EXIT_FAILURE 0
#define EXIT_SUCCESS 1

void exit(int status) __attribute__ ((__noreturn__));

#endif // _STDLIB_H