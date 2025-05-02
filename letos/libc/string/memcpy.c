#include <stdint.h>
#include <sys/cdefs.h>

// todo: optimize with word-sized copying O(n) => O(n) with smaller constant time

void memcpy(void* dst, const void* src, size_t bytes_length) {
    uint8_t* d = (uint8_t*) dst;
    uint8_t* s = (uint8_t*) src;

    for (size_t i = 0; i < bytes_length; i++) {
        d[i] = s[i]; 
    }
}
