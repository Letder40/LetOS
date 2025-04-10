#ifndef ARCH_I386_VGA_H
#define ARCH_I386_VGA_H

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

#endif
