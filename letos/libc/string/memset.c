#include <string.h>
#include <stdint.h>

void memset(void* dst, int value, size_t size) {
    uint8_t* d = (uint8_t*) dst;
    for (uint8_t i = 0; i < size; i++) {
        d[i] = (uint8_t)value;
    }
}
