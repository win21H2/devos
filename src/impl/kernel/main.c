#include "print.h"
#include "input.h"

void kernel_main() {
    pre_boot();
    post_boot();
}

void pre_boot() {
    pClear();
    pSetColor(PRINT_COLOR_LIGHT_RED, PRINT_COLOR_BLACK);
    pStr("root sID: ", NULL);
    pRandomRoot();

    pSetColor(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
    pNewLine();
    pStrln("Welcome to devOS!");
    pStrln("OSK developed by 9662e103-129a");

    pNewLine();
    pStrln("Press any key to continue...");

    getKey();

    pNewLine();
    pStrln("Booting...");
}

void post_boot() {
    // TODO: turn into CLI (also, implement Delay function)
}