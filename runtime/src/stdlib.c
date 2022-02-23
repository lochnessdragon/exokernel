#include <stdlib.h>

#ifndef __kernel_libk
#include <unistd.h>
#endif
#ifndef __kernel_libk
void exit(int status) {
    _exit(status);
}
#endif

int abs(int x) {
	return x * ((x < 0) ? -1 : 1);
}

int itoa(char* buffer, int x, unsigned int base, bool isSigned) {
	char symbols[] = "0123456789abcdef";

	// error checking code to make sure that the base is in the range 2-16 2 = binary, 16 = hexadecimal
	if (base >= sizeof(symbols) || base <= 1) return 0;

	char *buf_start = buffer;
	int is_positive = x >= 0 || !isSigned;
	unsigned int absx = abs(x);

	// always do the first digit, so that a zero is not an empty string
	// this loop inserts the characters in a reverse order, therfore, it must be reversed later to get the string in the right order.
	do {
		*buffer = symbols[absx % base];
		absx /= base;
		buffer++;
	} while(absx);

	*buffer = '-'; // this will be overwritten by the null if the number is positive
  buffer -= is_positive;
  int length = (int)(buffer - buf_start + 1);
  buffer[1] = '\0';
	
	// reverses the string
	while(buffer > buf_start) {
		char temp = *buf_start;
		*(buf_start++) = *buffer;
		*(buffer--) = temp;
	}
	
	return length;
}