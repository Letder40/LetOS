#ifndef _STRING_H
#define _STRING_H

#include <sys/cdefs.h>
#include <stddef.h>
#include <stdint.h>

size_t strlen(const char*);
int strcmp(const void*, const void*);
char* strtok(const char*, const char delimiter);
void memcpy(void*, const void*, size_t);
void memset(void*, int value, size_t);

#endif
