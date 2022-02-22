#include <stdlib.h>

#ifndef __kernel_libk
#include <unistd.h>
#endif
#ifndef __kernel_libk
void exit(int status) {
    _exit(status);
}
#endif