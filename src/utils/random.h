#pragma once
#include <time.h>

// [min, max]
static int rand(int min, int max) {
    srand((unsigned int) time(NULL));
    return rand() % (max - min + 1) + min;
}