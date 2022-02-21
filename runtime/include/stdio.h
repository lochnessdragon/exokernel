#ifndef _STDIO_H
#define _STDIO_H

/**
 * STDIO types
 * see 7.19.1
 */

// size_t define (see 7.19.1)
#include "size_t.h"

#ifndef __kernel_libk
// FILE struct
// see 7.19.1
// only availabe in userspace mode.
typedef struct FILE {
	unsigned int fd;
} FILE;

// fpos_t
// see 7.19.1
// unique specification of all positions in a file.
typedef unsigned long fpos_t;
#endif

// NULL type (see 7.19.1)
#include "null.h"

#ifndef __kernel_libk
extern FILE* __STDIN; // 0 
extern FILE* __STDOUT; // 1
extern FILE* __STDERR; // 2

#define stderr __STDERR
#define stdin __STDIN
#define stdout __STDOUT
#endif

/**
 * STDIO functions
 * 
 */

#ifndef __kernel_libk
// 7.19.4 - Operations on Files (not accessible to kernels)
int remove(const char *filename);
#endif

int putchar(int c);
int puts(const char *s);

#endif // _STDIO_H