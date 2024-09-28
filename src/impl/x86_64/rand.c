#include "rand.h"
#include <stddef.h>

static unsigned int next = 1;

void srand(unsigned int seed) {
    next = seed;
}

int rand() {
    next = next * 1103515245 + 12345;
    return (unsigned int)(next / 65536) % 32768;
}

void genRandRoot(char* buffer, size_t length) {
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    size_t charset_size = sizeof(charset) - 1;

    for (size_t i = 0; i < length; i++) {
        int key = rand() % charset_size;
        buffer[i] = charset[key];
    }
    buffer[length] = '\0';
}