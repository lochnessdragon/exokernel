#include "compat_checks.h"

#include <cpuid.h>
#include <stddef.h>
#include <stdio.h>

bool processor_is_supported() {
	if(!can_use_cpuid()) {
		puts("[ ERR ] CPUID is not supported, so we can not check the processor for supported features!");
		return false;
	}
		
	// check if x64 is available
	if(!is_x86_64_available()) {
		puts("[ ERR ] x64 is not available on this computer, please install the exokernel on a computer with the amd64 architecture.");
		return false;
	}

	return true;
}

bool can_use_cpuid() {
	unsigned int regular = __get_cpuid_max(0x0, NULL);
	unsigned int extended = __get_cpuid_max(0x80000000, NULL);
	return regular > 0 && extended > 0;
}

bool is_x86_64_available() {
	unsigned int eax, ebx, ecx, edx = 0;
	__get_cpuid(0x80000001, &eax, &ebx, &ecx, &edx);
	
	return edx & bit_LM; // check for long mode
}