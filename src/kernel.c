#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Hardware text mode cons

typedef enum {
    VGA_COLOR_BLACK,
    VGA_COLOR_BLUE,
    VGA_COLOR_GREEN,
    VGA_COLOR_CYAN,
    VGA_COLOR_RED,
    VGA_COLOR_MAGENTA,
    VGA_COLOR_BROWN,
    VGA_COLOR_LIGHT_GREY,
    VGA_COLOR_DARK_GREY,
    VGA_COLOR_LIGHT_BLUE,
    VGA_COLOR_LIGHT_GREEN,
    VGA_COLOR_LIGHT_CYAN,
    VGA_COLOR_LIGHT_RED,
    VGA_COLOR_LIGHT_MAGENTA,
    VGA_COLOR_LIGHT_BROWN,
    VGA_COLOR_LIGHT_WHITE,
} VGA_COLOR;

typedef uint8_t color;
/* example red with green background: 
 * red: 0x00000100
 * green: 0x00000010
 * green_background: 0x00000100 << 4 = 0x00100000
 * red_fg with green_background: 0x00100000 | 0x00000010 = 0x00100010
*/  
static inline color vga_entry_color(VGA_COLOR foreground, VGA_COLOR background) {
    return foreground | background << 4;
}

static inline uint16_t vga_entry(uint8_t uc, color color) {
    return (uint16_t) uc | (uint16_t) color << 8;
}

size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len] != '\0')
        len++;
    return len;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_initialialize(void) {
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK);
    terminal_buffer = (uint16_t*) 0xB8000;

    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH  + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}

void terminal_setcolor(uint8_t color) {
    terminal_color = color;
}

void terminal_putentryat(char c, color color, size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(c, color);
}

void terminal_scroll_down() {
    size_t i = 0;
    while (i < VGA_WIDTH)
        terminal_buffer[i++] = 0;

    size_t x = 0;
    while (i < VGA_WIDTH * VGA_WIDTH)
        terminal_buffer[x++] = terminal_buffer[i++];

    terminal_row -= 2;
}

void terminal_putchar(char c) {
    terminal_putentryat(c, terminal_color, terminal_column, terminal_row);

    if (++terminal_column == VGA_WIDTH) {
        terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT)
            terminal_scroll_down();
    }
}

void terminal_newline() {
    if (++terminal_row == VGA_HEIGHT)
        terminal_scroll_down();

    terminal_column = 0;
}

void terminal_write(const char* data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        if (data[i] == '\n')
            terminal_newline();
        else 
            terminal_putchar(data[i]);
    }
}

void terminal_writestring(const char* data) {
    terminal_write(data, strlen(data));
}

#define BANNER "88                                 ,ad8888ba,     ad88888ba   \n88                        ,d      d8\"'    `\"8b   d8\"     \"8b  \n88                        88     d8'        `8b  Y8,          \n88           ,adPPYba,  MM88MMM  88          88  `Y8aaaaa,    \n88          a8P_____88    88     88          88    `\"\"\"\"\"8b,  \n88          8PP\"\"\"\"\"\"\"    88     Y8,        ,8P          `8b  \n88          \\\"8b,   ,aa    88,     Y8a.    .a8P   Y8a     a8P  \n88888888888  `\"Ybbd8\"'    \"Y888    `\"Y8888Y\"'     \"Y88888P\"   \n"

void kernel_main(void) {
    terminal_initialialize();
    
    terminal_writestring(BANNER);
}
