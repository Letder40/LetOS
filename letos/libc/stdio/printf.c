#include <limits.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

int vprintf(const char* restrict format, va_list args) {
    int printed_chars = 0;

    while (*format != '\0') {
        if (*format == '%' && *(format + 1) == '%') {
            putchar('%');
            format += 2;
            printed_chars++;
            continue;
        }

        if (*format != '%') {
            putchar(*format++);
            printed_chars++;
            continue;
        }


        switch (*(++format)) {
        case 'c':
            char c = va_arg(args, int);
            putchar(c);
            printed_chars++;
            break;
        case 's':
            char* str = va_arg(args, char*);
            while (*str != '\0') {
                putchar(*str++);
                printed_chars++;
            }
            break;
        case 'd':
            int d = va_arg(args, int);

            char buf[32];
            int i = 0;

            if (d == 0) {
                putchar('0');
                printed_chars++;
                break;
            }

            if (d < 0) {
                putchar('-');
                printed_chars++;
                d = -d;
            }
            
            while (d > 0) {
                buf[i++] = (d % 10) + '0';
                d /= 10;
            }

            while (i > 0) {
                putchar(buf[--i]);
                printed_chars++;
            }

            break;
        default:
            putchar(*format);
            printed_chars++;
            break;
        }

        format++;

    }
    return printed_chars;
}

int printf(const char* restrict format, ...) {
    va_list args;
    va_start(args, format);
    int result = vprintf(format, args);
    va_end(args);
    return result;
}
