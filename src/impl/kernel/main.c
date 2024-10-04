#include "print.h"
#include "input.h"

// TODO: figure out how to do inline text coloring
/* EXAMPLE DECLARATION:
pStrC("Hello world!", 12, blue, black);
pStrlnC("Hello world!", blue, black);
*/

void kernel_main() {
    pClear();
    pSetColor(PRINT_COLOR_LIGHT_GRAY, PRINT_COLOR_BLACK);
    pStr("root sID: ", 10);
    pSetColor(PRINT_COLOR_LIGHT_BLUE, PRINT_COLOR_BLACK);
    pRandomRoot();

    pNewLine();
    pSetColor(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
    pNewLine();
    pStrln("Welcome to devOS!");
    pStrln("OSK developed by 9662e103-129a");
    pNewLine();

    char buffer[256];
    while(1) {
        readLine(buffer, sizeof(buffer));
    }
}