#ifndef RISCV_STRING_H
#define RISCV_STRING_H
#include <stddef.h>

// Memory
void* memcpy(void *restrict dest, const void *restrict src, size_t n);
void* memmove(void *dest, const void *src, size_t n);
void* memset(void *dest, int c, size_t n);
void* memchr(const void *s, int c, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);


// String
char* strrchr(const char *s, int c);
size_t strnlen(const char *s, size_t maxlen);
size_t strlen(const char *str);
const char *strchr(const char *s, int c);
unsigned long int strtoul (const char* str, char** endptr, int base);

#endif //RISCV_STRING_H
