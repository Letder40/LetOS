#include <stddef.h>
#include <stdint.h>

static char* next_token = NULL;

// single delimiter implementation (non standard)
char* strtok(char* str, const char delimiter) {
    if (str == NULL)
        str = next_token;

    if (str == NULL || *str == '\0') {
        next_token = NULL;
        return NULL;
    }

    char* token = str;

    while (*str && *str != delimiter) {
        str++;
    }

    if (*str) {
        *str = '\0';
        next_token = str + 1;
    } else {
        next_token = NULL;
    }

    return token;
}
