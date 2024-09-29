#include "input.h"
#include <stddef.h>

static inline uint8_t inb(uint16_t port) {
    uint8_t result;
    __asm__ volatile ("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

static inline void outb(uint16_t port, uint8_t data) {
    __asm__ volatile ("outb %0, %1" : : "a"(data), "Nd"(port));
}

static char scancode_to_ascii[] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', 
    '9', '0', '-', '=', '\b', /* Backspace */
    '\t', /* Tab */
    'q', 'w', 'e', 'r', /* 19 */
    't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', /* Enter key */
    0, /* 29   - Control */
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', /* 39 */
    '\'', '`', 0, /* Left shift */
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', /* 49 */
    'm', ',', '.', '/', 0, /* Right shift */
    '*',
    0,  /* Alt */
    ' ',  /* Space bar */
    0,  /* Caps lock */
    0,  /* 59 - F1 key ... > */
    0, 0, 0, 0, 0, 0, 0, 0,
    0,  /* < ... F10 */
    0,  /* 69 - Num lock*/
    0,  /* Scroll Lock */
    0,  /* Home key */
    0,  /* Up Arrow */
    0,  /* Page Up */
    '-',
    0,  /* Left Arrow */
    0,
    0,  /* Right Arrow */
    '+',
    0,  /* 79 - End key*/
    0,  /* Down Arrow */
    0,  /* Page Down */
    0,  /* Insert Key */
    0,  /* Delete Key */
    0, 0, 0,
    0,  /* F11 Key */
    0,  /* F12 Key */
    0,  /* All other keys are undefined */
};

char getKey() {
    uint8_t scancode;
    char key = 0;

    // Wait for the keyboard buffer to be full
    while (!(inb(KEYBOARD_STATUS_PORT) & KEYBOARD_STATUS_MASK_OUT_BUF));

    // Read the scancode from the keyboard data port
    scancode = inb(KEYBOARD_DATA_PORT);

    // Convert scancode to ASCII character
    if (scancode < sizeof(scancode_to_ascii)) {
        key = scancode_to_ascii[scancode];
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
        pChar(c); // Echo the character to the screen
    }
    buffer[length] = '\0';
}