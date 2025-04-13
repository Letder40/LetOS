#include <stdio.h>

#ifdef __is_kernel__
#include <kernel/tty.h>
#endif

int putchar(int __c) {
#ifdef __is_kernel__
	char c = (char) __c;
	terminal_putchar(c);
#else
    // write syscall
#endif
	return __c;
}
