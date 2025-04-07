#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>
#include <stdbool.h>

#define BANNER "\n88                                 ,ad8888ba,     ad88888ba   \n88                        ,d      d8\"'    `\"8b   d8\"     \"8b  \n88                        88     d8'        `8b  Y8,          \n88           ,adPPYba,  MM88MMM  88          88  `Y8aaaaa,    \n88          a8P_____88    88     88          88    `\"\"\"\"\"8b,  \n88          8PP\"\"\"\"\"\"\"    88     Y8,        ,8P          `8b  \n88          \\\"8b,   ,aa    88,     Y8a.    .a8P   Y8a     a8P  \n88888888888  `\"Ybbd8\"'    \"Y888    `\"Y8888Y\"'     \"Y88888P\"   \n\n\n"

void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);

#include "debug.h"
static inline void kernel_debug(const char* str) {
#ifdef _DEBUG
    if (_DEBUG) {
        terminal_writestring(str);
    }
#endif
}

#endif
