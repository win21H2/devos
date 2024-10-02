#include "print.h"
#include "input.h"

/* 
TODO:
- Implement delay function
- Implement basic CLI (including interfacing with text)
- Try to get it to echo out the text the user is inputting (i.e. displaying the characters being typed)
*/

void kernel_main() {
    pClear();
    pSetColor(PRINT_COLOR_LIGHT_RED, PRINT_COLOR_BLACK);
    pStr("root sID: ", NULL);
    pRandomRoot();

    pSetColor(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
    pNewLine();
    pStrln("Welcome to devOS!");
    pStrln("OSK developed by 9662e103-129a");

    pNewLine();

    while(1) {
        getKey();
    }
}