#include <string.h>

void test_strlen() {
	assert(strlen("Hello") == 5);
	assert(strlen("") == 0);
	assert(strlen(NULL) == 0);
}