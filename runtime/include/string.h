#pragma once
#include <stddef.h>
#ifdef __cplusplus
extern "C" {
#endif

void* memcpy(void* restrict destination, const void* restrict source, size_t len);
void* memmove(void* destination, const void* source, size_t len);

char* strcpy(char* restrict dest, const char* restrict src);
char* strncpy(char* restrict dest, const char* restrict src, size_t len);

char* strcat(char* restrict a, const char* restrict b);
char* strncat(char* restrict a, const char* restrict b, size_t len);

// compare functions 
int memcmp(const void* s1, const void* s2, size_t len);
int strcmp(const char* s1, const char* s2);
int strcoll(const char* s1, const char* s2);
int strncmp(const char* s1, const char* s2, size_t len);

size_t strxfrm(char* restrict s1, const char* restrict s2, size_t len);
void* memchr(const void* s, int c, size_t n);
char* strchr(const char* s, int c);
size_t strcspn(const char* s1, const char* s2);
char* strpbrk(const char* s1, const char* s2);
char* strrchr(const char* s1, int c);
size_t strspn(const char* s1, const char* s2);
char* strstr(const char* s1, const char* s2);
char* strtok(char* restrict s1, const char* s2);

// miscellaneous functions
void* memset(void* dest, int data, size_t len);
char* strerror(int errnum);
size_t strlen(const char* str);

#ifdef __cplusplus
}
#endif