#ifndef STDIO_H
#define STDIO_H

#define printf(...)                                                            \
    {                                                                          \
        extern void terminal_writestring(const char *);                        \
        terminal_writestring(__VA_ARGS__);                                     \
    }

#endif
