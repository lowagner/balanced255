#pragma once
#include "config255.h"

void unsafe255_from_int(balanced255 a, int carry);
void unsafe255_add_int(balanced255 a, int carry);

void unsafe255_from255_plus_int(balanced255 a, balanced255 b, int carry);
void unsafe255_add255(balanced255 a, balanced255 b);

void unsafe255_from_negative255_plus_int(balanced255 a, balanced255 b, int carry);
void unsafe255_subtract255(balanced255 a, balanced255 b);

void unsafe255_multiply255_with_int(balanced255 a, balanced255 b, int multiplier);
void unsafe255_gradeschool_multiply_nonzero255(
    balanced255 result, balanced255 partial_sum, balanced255 a, balanced255 b);

int unsafe_largest_int_multiple_and_subtract255(
    balanced255 partial, balanced255 remainder, balanced255 divider);
balanced255 unsafe_quotient_remainder255(balanced255 numerator, balanced255 denominator);

