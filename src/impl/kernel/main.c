#include "print.h"

void kernel_main() {

    pClear();
    pSetColor(PRINT_COLOR_LIGHT_RED, PRINT_COLOR_BLACK);
    pStr("root sID: ", NULL);
    pRandomRoot();

    pSetColor(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
    pNewLine();
    pStrln("Welcome to devOS!");
    pStrln("This is a simple OSK written in C, by 9662e103-129a, for the x86 architecture.");

    
}