#include <stdint.h>
#include <stdbool.h>

#include <string.h>
#include <sys/cdefs.h>
#include <stdio.h>
#include <stdlib.h>

#include <letos/tty.h>
#include <letos/keymaps.h>

#include <letos/debug.h>

extern volatile uint8_t input_buffer[256];
extern volatile uint8_t input_read_index;
extern volatile uint8_t input_write_index;

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

#define OUTPUT_LEN 255

char last_output[OUTPUT_LEN] = {0};

void set_output(char* output, bool print) {
    strcpy(last_output, output);
    if (print) {
        printf("\n%s", output);
    }
}

void last() {
    printf("\n%s", last_output);
}

void echo(char* str) {
    if (str == NULL) {
        printf("\n");
        return;
    }
    set_output(str, true);
}

void clear() {
    terminal_initialize(); 
}

void calc(char** args) {
    int n1;
    if (!strcmp(args[0], "last"))
        n1 = atoi(last_output);
    else 
        n1 = atoi(args[0]); 

    int n2;
    if (!strcmp(args[2], "last"))
        n2 = atoi(last_output);
    else 
        n2 = atoi(args[2]); 

    char operator = *args[1]; 
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
            if (n1 == 0 || n2 == 0) {
                echo("Division by 0 leads to undefined behaviour ;D");
                return;
            }
            result = n1 / n2;
            break;
        case '%':
            result = n1 % n2;
            break;
        default:
            printf("operator: %c\n", operator);
            echo("invalid operation");
            return;
    }

    int d = result;
    char buf[33] = {0};
    int i = 32;

    buf[i--] = '\0';

    if (d == 0) {
        set_output("0", false);
        goto print_result;
    }

    if (d < 0) {
        buf[i--] = '-';
    }
    
    while (d > 0) {
        buf[i--] = (d % 10) + '0';
        d /= 10;
    }

    char* num_start = (char*) buf;
    while (!*num_start) num_start++; 

    set_output(num_start, false);

print_result:
    printf("\n%d %c %d = %d\n", n1, operator, n2, result);
}

#define COMAND_LEN OUTPUT_LEN
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
        echo(strtok(NULL, '\0'));
    } else if (!strcmp(command, "clear")) {
        clear();
    } else if (!strcmp(command, "last")) {
        last();
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
    for(;;) {
        asm volatile ("hlt");
        while (input_read_index != input_write_index) {
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
                if (!keymap_printable[scancode] || !keymap[scancode]) {
#ifdef _DEBUG
                    printf("\nUndetected scancode: %d\n", scancode);
                    printf("\nTrying to print scancode: %c\n", keymap[scancode]);
#else
                    printf("?");
#endif
                    continue; 
                }
                command_write(ch);
                printf("%c", ch);
                break;
            }
        }
    }
}
