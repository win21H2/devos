#pragma once

#include <stdint.h>
#include <stddef.h>

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_STATUS_MASK_OUT_BUF 1

#define SC_ESC 0x01
#define SC_1 0x02
#define SC_2 0x03
#define SC_3 0x04
#define SC_4 0x05
#define SC_5 0x06
#define SC_6 0x07
#define SC_7 0x08
#define SC_8 0x09
#define SC_9 0x0A
#define SC_0 0x0B
#define SC_MINUS 0x0C
#define SC_EQUALS 0x0D
#define SC_BACKSPACE 0x0E
#define SC_TAB 0x0F
#define SC_Q 0x10
#define SC_W 0x11
#define SC_E 0x12
#define SC_R 0x13
#define SC_T 0x14
#define SC_Y 0x15
#define SC_U 0x16
#define SC_I 0x17
#define SC_O 0x18
#define SC_P 0x19
#define SC_LEFT_BRACKET 0x1A
#define SC_RIGHT_BRACKET 0x1B
#define SC_ENTER 0x1C
#define SC_A 0x1E
#define SC_S 0x1F
#define SC_D 0x20
#define SC_F 0x21
#define SC_G 0x22
#define SC_H 0x23
#define SC_J 0x24
#define SC_K 0x25
#define SC_L 0x26
#define SC_SEMICOLON 0x27
#define SC_APOSTROPHE 0x28
#define SC_GRAVE 0x29
#define SC_BACKSLASH 0x2B
#define SC_Z 0x2C
#define SC_X 0x2D
#define SC_C 0x2E
#define SC_V 0x2F
#define SC_B 0x30
#define SC_N 0x31
#define SC_M 0x32
#define SC_COMMA 0x33
#define SC_PERIOD 0x34
#define SC_SLASH 0x35
#define SC_SPACE 0x39

// arrow keys (todo: implement functionality - try to find correct scan codes for these keys)
// #define SC_LEFTARR 0x75
// #define SC_RIGHTARR 0x77

char getKey();
void readLine(char* buffer, size_t max_length);