#include <limits.h>

int atoi(const char* str) {
    if (!str) return 0;

    while (*str == ' ' || *str == '\t') str++;

    int sign = 1;
    if (*str == '-') {
        sign = -1;
        str++;
    }
    
    long result = 0;

    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;

        if (result * sign > INT_MAX) return INT_MAX;
        if (result * sign < INT_MIN) return INT_MIN;
    }

    return (int) result * sign;
}
