#ifndef STDIO_H
#define STDIO_H

#include <stdarg.h>
#include <sys/cdefs.h>

int putchar(int __c);

int printf(const char* format, ...);
int vprintf(const char* format, va_list args);

#endif
