#ifndef _COMPAT_CHECKS_H
#define _COMPAT_CHECKS_H

#include <stdbool.h>

bool can_use_cpuid();
bool is_x86_64_available();

#endif // _COMPAT_CHECKS_H