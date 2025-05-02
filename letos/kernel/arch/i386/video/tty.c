#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "vga.h"

void terminal_writestring(const char*);

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_initialize(void) {
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK);
    terminal_buffer = VGA_MEMORY;

    for (size_t i = 0; i < VGA_HEIGHT * VGA_WIDTH; i++) {
        terminal_buffer[i] = vga_entry(' ', terminal_color);
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

    terminal_row -= 1;
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
        switch (data[i]) {
        case '\n':
            terminal_newline();
            break;
        case '\t':
            terminal_writestring("    ");
            break;
        case '\b':
            if (terminal_column == 0) return;
            terminal_column--;
            terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
            break;
        default:
            terminal_putchar(data[i]);
            break;
        }
    }
}

void terminal_writestring(const char* data) {
    terminal_write(data, strlen(data));
}
