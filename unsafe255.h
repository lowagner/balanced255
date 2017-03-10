#pragma once
#include "config255.h"

void unsafe255_from_int(balanced255 a, int carry);
void unsafe255_add_int(balanced255 a, int carry);

void unsafe255_from255_plus_int(balanced255 a, balanced255 b, int carry);
void unsafe255_add255(balanced255 a, balanced255 b);

void unsafe255_from_negative255_plus_int(balanced255 a, balanced255 b, int carry);
void unsafe255_subtract255(balanced255 a, balanced255 b);

void unsafe255_multiply255_with_int(balanced255 a, balanced255 b, int multiplier);
