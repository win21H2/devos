#include "print.h"
#include "rand.h"

static const size_t NUM_COLS = 80;
static const size_t NUM_ROWS = 25;

struct Char {
    uint8_t character;
    uint8_t color;
};

struct Char* buffer = (struct Char*) 0xb8000;
size_t col, row = 0;
uint8_t color = PRINT_COLOR_WHITE | PRINT_COLOR_BLACK << 4;

void ClrRow(size_t row) {
    struct Char empty = { ' ', color };
    struct Char* row_start = buffer + NUM_COLS * row;
    for (size_t col = 0; col < NUM_COLS; col++) {
        row_start[col] = empty;
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
        struct Char* src = buffer + NUM_COLS * row;
        struct Char* dest = buffer + NUM_COLS * (row - 1);
        for (size_t col = 0; col < NUM_COLS; col++) {
            dest[col] = src[col];
        }
    }

    ClrRow(NUM_ROWS - 1);
}

void pChar(char character) {
    if (character == '\n') {
        pNewLine();
        return;
    }

    if (col >= NUM_COLS) {
        pNewLine();
    }

    buffer[col + NUM_COLS * row] = (struct Char) { (uint8_t) character, color };
    col++;
}

void pStr(char* str) {
    for (size_t i = 0; str[i] != '\0'; i++) {
        pChar(str[i]);
    }
}

void pStrln(char* str) {
    pStr(str);
    pNewLine();
}

void pSetColor(uint8_t foreground, uint8_t background) {
    color = foreground | (background << 4);
}

void pRandomRoot() {
    char root[9];
    srand((unsigned int)time());
    genRandRoot(root, 10);
    pStr(root);
}
