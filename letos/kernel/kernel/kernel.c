#include <kernel/tty.h>

#define BANNER "88                                 ,ad8888ba,     ad88888ba   \n88                        ,d      d8\"'    `\"8b   d8\"     \"8b  \n88                        88     d8'        `8b  Y8,          \n88           ,adPPYba,  MM88MMM  88          88  `Y8aaaaa,    \n88          a8P_____88    88     88          88    `\"\"\"\"\"8b,  \n88          8PP\"\"\"\"\"\"\"    88     Y8,        ,8P          `8b  \n88          \\\"8b,   ,aa    88,     Y8a.    .a8P   Y8a     a8P  \n88888888888  `\"Ybbd8\"'    \"Y888    `\"Y8888Y\"'     \"Y88888P\"   \n"

void kernel_main(void) {
    terminal_initialize();
    
    terminal_writestring(BANNER);
}
