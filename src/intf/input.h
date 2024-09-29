#pragma once

#include <stdint.h>
#include <stddef.h>

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_STATUS_MASK_OUT_BUF 1

char getKey();
void pReadLine(char* buffer, size_t max_length);
