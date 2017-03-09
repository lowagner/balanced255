#pragma once
#include "config255.h"

int is_zero255(balanced255 a);
int is_nonzero255(balanced255 a);
int is_positive255(balanced255 a);
int is_negative255(balanced255 a);

int are_equal255(balanced255 a, balanced255 b);

int8_t carry_next_digit255(int *carry);
balanced255 add255(balanced255 a, balanced255 b);

void increment255(balanced255 *aptr);
void decrement255(balanced255 *aptr);

balanced255 multiply255(balanced255 a, balanced255 b);
