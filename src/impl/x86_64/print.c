#include "print.h"
#include "rand.h"

const static size_t NUM_COLS = 80;
const static size_t NUM_ROWS = 25;

struct Char {
    uint8_t character;
    uint8_t color;
};

struct Char* buffer = (struct Char*) 0xb8000;
size_t col = 0;
size_t row = 0;
uint8_t color = PRINT_COLOR_WHITE | PRINT_COLOR_BLACK << 4;

void ClrRow(size_t row) {
    struct Char empty = (struct Char) {
        character: ' ',
        color: color,
    };

    for (size_t col = 0; col < NUM_COLS; col++) {
        buffer[col + NUM_COLS * row] = empty;
    }
}

void pClear() {
    for (size_t i = 0; i < NUM_ROWS; i++) {
        ClrRow(i);
    }
}

void pNewLine() {
    col = 0;

    if (row < NUM_ROWS - 1) {
        row++;
        return;
    }

    for (size_t row = 1; row < NUM_ROWS; row++) {
        for (size_t col = 0; col < NUM_COLS; col++) {
            struct Char character = buffer[col + NUM_COLS * row];
            buffer[col + NUM_COLS * (row - 1)] = character;
        }
    }

    ClrRow(NUM_COLS - 1);
}

void pChar(char character) {
    if (character == '\n') {
        pNewLine();
        return;
    }

    if (col > NUM_COLS) {
        pNewLine();
    }

    buffer[col + NUM_COLS * row] = (struct Char) {
        character: (uint8_t) character,
        color: color,
    };

    col++;
}

void pStr(char* str) {
    for (size_t i = 0; 1; i++) {
        char character = (uint8_t) str[i];

        if (character == '\0') {
            return;
        }

        pChar(character);
    }
}

void pStrln(char* str) {
    pStr(str);
    pNewLine();
}

void pSetColor(uint8_t foreground, uint8_t background) {
    color = foreground + (background << 4);
}

void pRandomRoot() {
    char root[9];
    srand((unsigned int)time());
    genRandRoot(root, 10);
    pStr(root);
}