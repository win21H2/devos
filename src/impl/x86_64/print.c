/* TODO 
- Implement text underlining
- Implement text bold'ing
*/

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
    if (col >= NUM_COLS) {
        pNewLine();
    }

    buffer[col + NUM_COLS * row] = (struct Char) { (uint8_t) character, color };
    col++;
}

void pCliInput(char character) {
    if (character == '\n') {
        pNewLine();
        return;
    }

    if (character == '\b') {
        if (col > 11) {
            col--;
            buffer[col + NUM_COLS * row] = (struct Char) { ' ', color };
        } else if (row > 4) {
            row--;
            col = NUM_COLS - 1;
            while (col > 0 && buffer[col + NUM_COLS * row].character == ' ') {
                col--;
            }
            buffer[col + NUM_COLS * row] = (struct Char) { ' ', color };
        }
        return;
    }

    pChar(character);
}

size_t strLen(const char* str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

void pStr(const char* str, size_t len) {
    for (size_t i = 0; i < len && str[i] != '\0'; i++) {
        pChar(str[i]);
    }
}

void pStrln(const char* str) {
    pStr(str, strLen(str));
    pNewLine();
}

void pSetColor(uint8_t foreground, uint8_t background) {
    color = foreground | (background << 4);
}

void pRandomRoot() {
    char root[9];
    srand((unsigned int)time());
    genRandRoot(root, 10);
    pStr(root, strLen(root));
}