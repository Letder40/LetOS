#include <stdio.h>
#include <stdint.h>

#include "../../include/io.h"
#include "../../include/interrupts.h"

volatile uint8_t input_buffer[255];
volatile uint8_t input_index;

void keyboard_handler() {
    uint8_t scancode = inb(0x60);
    if (input_index == 255) {
        input_index = 0;
    }

    input_buffer[input_index++] = scancode;
    printf("key_pressed\n");
}

ISR_WRAPPER(keyboard_isr, keyboard_handler)
