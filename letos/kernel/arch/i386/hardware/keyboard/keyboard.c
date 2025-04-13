#include <stdint.h>

#include "../../include/io.h"
#include "../../include/interrupts.h"

volatile uint8_t input_buffer[256];
volatile uint8_t input_write_index;
volatile uint8_t input_read_index;

void keyboard_handler() {
    uint8_t scancode = inb(0x60);
    uint8_t input_write_next = input_write_index + 1;

    if (input_write_next != input_read_index) {
        input_buffer[input_write_index++] = scancode;
    }
}

ISR_WRAPPER(keyboard_isr, keyboard_handler)
