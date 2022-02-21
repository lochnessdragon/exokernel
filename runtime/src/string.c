#include <string.h>

// very slow and basic memcpy
// some optimizations would include waiting for the pointer to become 64bit aligned,
// and then copy 4 bytes or something like that
void* memcpy(void* restrict destination, const void* restrict source, size_t len) {
    for(size_t i = 0; i < len; i++) {
        (*((char*)destination+i)) = (*((char*)source+i));
    }
    return destination;
}

// could also be optimized
void* memmove(void* destination, const void* source, size_t len) {
    // check the direction to copy in
    if(source > destination) {
        for(size_t i = 0; i < len; i++) {
            *((char*)destination+i) = *((char*)source+i);
        }
    } else {

    }
    // copy in that direction

    return destination;
}

void* memset(void* dest, int data, size_t len) {
    for(size_t i = 0; i < len; i++) {
        *((unsigned char*) dest+i) = (unsigned char) data;
    }
    
    return dest;
}

size_t strlen(const char* str) {
    int count = 0;
    char c = *str;

    while(c != '\0') {
        str++;
        c=*str;
    }

    return count;
}