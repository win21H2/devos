#include "print.h"

// TODO: IMPLEMENT USER INPUT

const static size_t NUM_COLS = 80; // Define a constant for the number of columns in the screen buffer.
const static size_t NUM_ROWS = 25; // Define a constant for the number of rows in the screen buffer.

struct Char { // Define a structure to represent a character on the screen.
    uint8_t character; // The ASCII value of the character.
    uint8_t color; // The color attribute of the character.
};

struct Char* buffer = (struct Char*) 0xb8000; // Define a pointer to the screen buffer located at memory address 0xb8000.
size_t col = 0; // Initialize the column position to 0.
size_t row = 0; // Initialize the row position to 0.
uint8_t color = PRINT_COLOR_WHITE | PRINT_COLOR_BLACK << 4; // Initialize the color attribute with white text on a black background.

void ClrRow(size_t row) { // Function to clear a specific row on the screen.
    struct Char empty = (struct Char) { // Create an empty character with a space and the current color.
        character: ' ',
        color: color,
    };

    for (size_t col = 0; col < NUM_COLS; col++) { // Loop through each column in the specified row.
        buffer[col + NUM_COLS * row] = empty; // Set each position in the row to the empty character.
    }
}

void pClear() { // Function to clear the entire screen.
    for (size_t i = 0; i < NUM_ROWS; i++) { // Loop through each row.
        ClrRow(i); // Clear the current row.
    }
}

void pNewLine() { // Function to handle a newline character.
    col = 0; // Reset the column position to 0.

    if (row < NUM_ROWS - 1) { // If the current row is not the last row.
        row++; // Move to the next row.
        return; // Exit the function.
    }

    for (size_t row = 1; row < NUM_ROWS; row++) { // Loop through each row starting from the second row.
        for (size_t col = 0; col < NUM_COLS; col++) { // Loop through each column.
            struct Char character = buffer[col + NUM_COLS * row]; // Get the character from the current position.
            buffer[col + NUM_COLS * (row - 1)] = character; // Move the character to the previous row.
        }
    }

    ClrRow(NUM_COLS - 1); // Clear the last row.
}

void pChar(char character) { // Function to print a single character.
    if (character == '\n') { // If the character is a newline.
        pNewLine(); // Handle the newline.
        return; // Exit the function.
    }

    if (col > NUM_COLS) { // If the column position exceeds the number of columns.
        pNewLine(); // Handle the newline.
    }

    buffer[col + NUM_COLS * row] = (struct Char) { // Set the character and color at the current position.
        character: (uint8_t) character,
        color: color,
    };

    col++; // Move to the next column.
}

void pStr(char* str) { // Function to print a string.
    for (size_t i = 0; 1; i++) { // Loop through each character in the string.
        char character = (uint8_t) str[i]; // Get the current character.

        if (character == '\0') { // If the character is the null terminator.
            return; // Exit the function.
        }

        pChar(character); // Print the current character.
    }
}

void pStrln(char* str) { // Function to print a string followed by a newline.
    pStr(str); // Print the string.
    pNewLine(); // Handle the newline.
}

void pSetColor(uint8_t foreground, uint8_t background) { // Function to set the color attribute.
    color = foreground + (background << 4); // Combine the foreground and background colors.
}
