/*TODO
- Implement right/left/up/down arrow keys
- Implement a flashing vertical cursor
*/

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

static const char scanCodeMap[256] = {
    [SC_ESC] = 0x1B,
    [SC_1] = '1', [SC_2] = '2', [SC_3] = '3', [SC_4] = '4', [SC_5] = '5', [SC_6] = '6', [SC_7] = '7', [SC_8] = '8', [SC_9] = '9', [SC_0] = '0',
    [SC_MINUS] = '-',
    [SC_EQUALS] = '=',
    [SC_BACKSPACE] = '\b',
    [SC_TAB] = '\t',
    [SC_Q] = 'q', [SC_W] = 'w', [SC_E] = 'e', [SC_R] = 'r', [SC_T] = 't', [SC_Y] = 'y', [SC_U] = 'u', [SC_I] = 'i', [SC_O] = 'o', [SC_P] = 'p',
    [SC_LEFT_BRACKET] = '[', [SC_RIGHT_BRACKET] = ']',
    [SC_ENTER] = '\n',
    [SC_A] = 'a', [SC_S] = 's', [SC_D] = 'd', [SC_F] = 'f', [SC_G] = 'g', [SC_H] = 'h', [SC_J] = 'j', [SC_K] = 'k', [SC_L] = 'l',
    [SC_SEMICOLON] = ';',
    [SC_APOSTROPHE] = '\'',
    [SC_GRAVE] = '`',
    [SC_BACKSLASH] = '\\',
    [SC_Z] = 'z', [SC_X] = 'x', [SC_C] = 'c', [SC_V] = 'v', [SC_B] = 'b', [SC_N] = 'n', [SC_M] = 'm',
    [SC_COMMA] = ',',
    [SC_PERIOD] = '.',
    [SC_SLASH] = '/',
    [SC_SPACE] = ' ',
};

char scancodeToChar(uint8_t scancode) {
    return scanCodeMap[scancode];
}

char getKey() {
    uint8_t scanCode;
    char key = 0;

    while (!(inb(KEYBOARD_STATUS_PORT) & KEYBOARD_STATUS_MASK_OUT_BUF));
    scanCode = inb(KEYBOARD_DATA_PORT);

    key = scancodeToChar(scanCode);

    return key;
}

void readLine(char* buffer, size_t max_length) {
    size_t length = 0;
    pStr("dOSS root> ", 11);
    while (length < max_length - 1) {
        char c = getKey();
        if (c == '\n') {
            pNewLine();
            break;
        }

        if (c == '\b') {
            if (length > 0) {
                length--;
                pInput(c);
            }
        } else if (c != 0) {
            buffer[length++] = c;
            pInput(c);
        }
    }
    
    buffer[length] = '\0';
}