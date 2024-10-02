#include "input.h"
#include "print.h"
#include <stddef.h>
#include <stdint.h>

extern uint8_t inb_asm(uint16_t port);
extern void outb_asm(uint16_t port, uint8_t data);

static inline uint8_t inb(uint16_t port) {
    return inb_asm(port);
}

static inline void outb(uint16_t port, uint8_t data) {
    outb_asm(port, data);
}

static char scancode_to_ascii[128] = {
    0,  27,
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',   
    '\t',
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',     
    0,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 
    0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',
    0,
    '*',
    0,
    ' ',
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    '-',
    0, 0, 0,
    '+',
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

char getKey() {
    uint8_t scancode;
    char key = 0;

    while (!(inb(KEYBOARD_STATUS_PORT) & KEYBOARD_STATUS_MASK_OUT_BUF));
    scancode = inb(KEYBOARD_DATA_PORT);

    if (scancode < sizeof(scancode_to_ascii)) {
        key = scancode_to_ascii[scancode];
    }

    if (key) {
        pChar(key);
    }

    return key;
}

void pReadLine(char* buffer, size_t max_length) {
    size_t length = 0;
    while (length < max_length - 1) {
        char c = getKey();
        if (c == '\n') {
            break;
        }

        buffer[length++] = c;
        pChar(c);
    }
    
    buffer[length] = '\0';
}