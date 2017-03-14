#pragma once
#include "config255.h"

static inline int abs(int x) {
    return (x < 0) ? -x : x;
}

int8_t carry_next_digit255(int *carry);
balanced255 add255(balanced255 a, balanced255 b);
balanced255 subtract255(balanced255 a, balanced255 b);

balanced255 negate255(balanced255 a);

void increment255(balanced255 *aptr);
void decrement255(balanced255 *aptr);

balanced255 multiply255(balanced255 a, balanced255 b);
balanced255 quotient_remainder255(balanced255 a, balanced255 b);
