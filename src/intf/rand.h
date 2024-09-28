#pragma once
#include <stddef.h>

void srand(unsigned int seed);
int rand();
void genRandRoot(char* buffer, size_t length);
unsigned long long time();