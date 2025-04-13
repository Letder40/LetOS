#include <stdint.h>
#include <stdio.h>
#include <letos/keymaps.h>

extern volatile uint8_t input_buffer[256];
extern volatile uint8_t input_read_index;

char keymap_es[128] = { KEYMAP_ES };
char keymap_es_printable[128] = { KEYMAP_ES_PRINTABLE_BMAP };

#define MAX_LEN 256

void kernel_shell() {
    printf("> ");
    while (1) {
        asm volatile ("hlt");
        uint8_t scancode = input_buffer[input_read_index++];

        if ((scancode & 0x80) == 0x80) {
            // key release
        } else {
            if (!keymap_es_printable[scancode]) {
                continue; 
            }
            switch (keymap_es[scancode]) {
            case RET:
                printf("\n");
                printf("> ");
                break;
            case TAB:
                printf("\t");
                break;
            default:
                printf("%c", keymap_es[scancode]);
                break;
            }
        }
    }
}
