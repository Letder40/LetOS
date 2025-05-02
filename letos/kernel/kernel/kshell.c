#include <stdint.h>
#include <stdbool.h>

#include <string.h>
#include <sys/cdefs.h>
#include <stdio.h>
#include <stdlib.h>

#include <letos/tty.h>
#include <letos/keymaps.h>

extern volatile uint8_t input_buffer[256];
extern volatile uint8_t input_read_index;

static char keymap_unshifted[] = { KEYMAP_ES };
static char keymap_shifted[] = { KEYMAP_ES_SHIFTED };
static bool keymap_printable[] = { KEYMAP_ES_PRINTABLE_BMAP };

char* keymap = keymap_unshifted; 
bool keymap_shifted_flag = 0;

void shift_keymap() {
    if (keymap_shifted_flag) {
        keymap = keymap_unshifted;
    } else {
        keymap = keymap_shifted;
    }

    keymap_shifted_flag ^= 1;
}

// Builtins

void echo(char* str) {
    if (str == NULL) {
        printf("\n");
        return;
    }
    printf("\n%s", str);
}

void clear() {
    terminal_initialize(); 
}

void calc(char** args) {
    int n1 = atoi(args[0]); 
    char operator = *args[1]; 
    int n2 = atoi(args[2]); 
    int result = 0;

    switch (operator) {
        case '+':
            result = n1 + n2;
            break;
        case '-':
            result = n1 - n2;
            break;
        case '*':
            result = n1 * n2;
            break;
        case '/':
            result = n1 / n2;
            break;
        case '%':
            result = n1 % n2;
            break;
        default:
            printf("invalid operation");
            return;
    }

    printf("\n%d %c %d = %d\n", n1, operator, n2, result);
}

#define COMAND_LEN 255
static char command_buffer[COMAND_LEN];
static uint8_t command_write_idx;

void command_write(uint8_t command_char) {
    if (command_write_idx == 20) {
        return;
    }

    command_buffer[command_write_idx++] = command_char;
}

void process_args(size_t argc, char** argv) {
    char* token = strtok(NULL, ' ');
    size_t idx = 0;
    while (token != NULL && idx < argc) {
        argv[idx] = token;
        token = strtok(NULL, ' ');
        idx++; 
    }    
}

void check_command() {
    command_buffer[command_write_idx] = '\0';

    if (!strlen(command_buffer)) return;

    char* command = strtok(command_buffer, ' ');

    if (!strcmp(command, "echo")) {
        echo(strtok(NULL, 0));
    } else if (!strcmp(command, "clear")) {
        clear();
    } else if (!strcmp(command, "calc")) {
        char* args[3];
        process_args(3, args);
        calc(args);
    } else {
        printf("\nInvalid command: %s", command);
    }

    memset(command_buffer, 0, COMAND_LEN);
    command_write_idx = 0;
}

// Kshell

void kernel_shell() {
    printf("> ");
    while (1) {
        asm volatile ("hlt");
        uint8_t scancode = input_buffer[input_read_index++];

        // release
        if ((scancode & 0x80) == 0x80) {
            scancode = scancode ^ 0x80;
            uint8_t ch = keymap[scancode];
            if (ch == SHF)
                shift_keymap();
            continue;
        }  

        // press
        uint8_t ch = keymap[scancode];
        switch (ch) {
        case BKM:
            shift_keymap();
            break;
        case SHF:
            shift_keymap();
            break;
        case RET:
            check_command();
            putchar('\n');
            printf("> ");
            break;
        case TAB:
            putchar('\t');
            break;
        case BSP:
            if (command_write_idx != 0) command_write_idx--;
            putchar('\b');
            break;
        default:
            if (!keymap_printable[scancode]) {
                continue; 
            }
            command_write(ch);
            printf("%c", ch);
            break;
        }
    }
}
