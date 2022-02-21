#include <stdio.h>
#include <stddef.h>

struct test {
	int a;
};

int main() {
	puts("Testing testing 123");
	int offset = offsetof(struct test, a);
	return 0;
}