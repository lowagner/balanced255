#include "balanced255.h"
#include "allocate255.h"
#include <string.h>

int abs(int x) {
    return (x < 0) ? -x : x;
}

void unsafe255_from_int(balanced255 a, int carry) {
    // a is zero, add carry.  a should be preallocated.
    while (carry)
        *a++ = carry_next_digit255(&carry);
    *a = -128;
}

void unsafe255_add_int(balanced255 a, int carry) {
    // a is (possibly) nonzero, add carry.  a should be preallocated.
    while (*a != -128) {
        carry += (int8_t)*a;
        *a++ = carry_next_digit255(&carry);
    }
    unsafe255_from_int(a, carry);
}

void unsafe255_from255_plus_int(balanced255 a, balanced255 b, int carry) {
    // a is "zero", add b and carry together to make the rest of a.  a should be preallocated.
    while (*b != -128) {
        carry += (int8_t)*b++;
        *a++ = carry_next_digit255(&carry);
    }
    unsafe255_from_int(a, carry);
}

void unsafe255_add255(balanced255 a, balanced255 b) {
    // add b to a.  a should be properly allocated to go as large as max(length255(a), length255(b)) + 1.
    int carry = 0;
    while (1) {
        if (*b == -128)
            return unsafe255_add_int(a, carry);
        if (*a == -128)
            return unsafe255_from255_plus_int(a, b, carry);
        carry += (int8_t)(*a) + (int8_t)(*b++); 
        *a++ = carry_next_digit255(&carry);
    }
}

void unsafe255_from_negative255_plus_int(balanced255 a, balanced255 b, int carry) {
    // a is "zero", add -b and carry together to make the rest of a.  a should be preallocated.
    while (*b != -128) {
        carry -= (int8_t)*b++;
        *a++ = carry_next_digit255(&carry);
    }
    unsafe255_from_int(a, carry);
}

void unsafe255_subtract255(balanced255 a, balanced255 b) {
    // add b to a.  a should be properly allocated to go as large as max(length255(a), length255(b)) + 1.
    int carry = 0;
    while (1) {
        if (*b == -128)
            return unsafe255_add_int(a, carry);
        if (*a == -128)
            return unsafe255_from_negative255_plus_int(a, b, carry);
        carry += (int8_t)(*a) - (int8_t)(*b++); 
        *a++ = carry_next_digit255(&carry);
    }
}

void unsafe255_multiply255_with_int(balanced255 a, balanced255 b, int multiplier) {
    // multiply b with multiplier, put into a (preallocated)
    int carry = 0;
    while (1) {
        if (*b == -128)
            return unsafe255_from_int(a, carry);
        carry += (int8_t)(*b++) * multiplier;
        *a++ = carry_next_digit255(&carry);
    }
}

void unsafe255_gradeschool_multiply_nonzero255(
    balanced255 result, balanced255 partial_sum, balanced255 a, balanced255 b)
{
    while (*b != -128) {
        if (*b) {
            unsafe255_multiply255_with_int(partial_sum, a, *b);
            #if DEBUG > 9000
            printf("adding partial_sum...\n  ");
            print255(partial_sum);
            #endif
            unsafe255_add255(result, partial_sum);
        } 
        else if (*result == -128) {
            *result = 0;
            *(result+1) = -128;
        }
        ++b;
        ++result;
    }
}

int unsafe_largest_int_multiple_and_subtract255(
    balanced255 partial, balanced255 remainder, balanced255 denominator, int len_denominator) 
{
    // partial is some work space, find divider = remainder/divider
    // why unsafe:  you must be able to assume the result (divider) is small enough to fit in an int.
    int compare = compare255(remainder, denominator);
    switch (compare) {
        case -1: // remainder < denominator
            return 0;
        case 0: // remainder == denominator
            *remainder = 0;
            return 1;
    }
    int denominator_leading_value = denominator[len_denominator-2];
    // find largest multiple of denominator smaller than current remainder
    int divider = value255(remainder+len_denominator-2) / denominator_leading_value;
    // value255 should not be more than 255*255 + 255, 
    if (abs(divider) > 255) {
        fprintf(stderr, "\n!!!\nimpossible digit found!!!  %d\n", divider);
        return 0;
    }
    unsafe255_multiply255_with_int(partial, denominator, divider);
    switch ((compare = compare255(partial, remainder))) {
        case -1:
            // partial < remainder
            // need to add denominator to partial until > remainder, then subtract one.
            // "restorative" division
            do {
                #if DEBUG > 9000
                printf("partial was less than remainder, adding another denominator\n");
                printing255(partial);
                printf(" < ");
                printing255(remainder);
                printf("\n");
                #endif
                unsafe255_add255(partial, denominator);
                ++divider;
            } while ((compare = compare255(partial, remainder)) < 0);
            if (compare == 0) {
                *remainder = -128;
                break;
            }
            unsafe255_subtract255(partial, denominator);
            --divider;
            unsafe255_subtract255(remainder, partial);
            break;
        case 0:
            *remainder = -128;
            break;
        case 1:
            // partial > remainder
            // need to subtract denominator from partial until < remainder.
            do {
                #if DEBUG > 9000
                printf("partial was greater than remainder, subtracting another denominator\n");
                printing255(partial);
                printf(" < ");
                printing255(remainder);
                printf("\n");
                #endif
                unsafe255_subtract255(partial, denominator);
                --divider;
            } while ((compare = compare255(partial, remainder)) > 0);
            if (compare == 0) {
                *remainder = -128;
                break;
            }
            unsafe255_subtract255(remainder, partial);
            break;
    }
    return divider;
}

balanced255 unsafe_quotient_remainder255(balanced255 numerator, balanced255 denominator) {
    // denominator must not be zero, also numerator and denominator should be positive;
    balanced255 quotient;
    switch (compare255(numerator, denominator)) {
        case -1: // numerator < denominator
            quotient = allocate255(1);
            *quotient = -128; 
            return quotient;
        case 0: // numerator == denominator
            quotient = allocate255(2);
            quotient[0] = 1;
            quotient[1] = -128; 
            *numerator = -128; // zero numerator
            return quotient;
    }
    balanced255 remainder;
    balanced255 quotient_tail;
    balanced255 partial;
    int len_denominator;
    {
        int len_numerator;
        len_numerator = length255(numerator);
        len_denominator = length255(denominator);
        int quotient_length = len_numerator - len_denominator + 2;
        // if N = [ 2, 3, 4, 5, -128 ]  -> length 5
        // and D= [ 2, 3, 4, -128 ] -> length 4
        // then Q = [ _, _, -128 ] -> length 3
        quotient = allocate255(quotient_length);
        quotient[quotient_length-1] = -128;
        remainder = numerator + quotient_length - 2;
        quotient_tail = quotient+quotient_length-2;
        partial = allocate255(len_denominator+1);
        *partial = -128;
    }
    #if DEBUG > 9000
    printf("starting at numerator position (initial remainder):\n ");
    print255(remainder);
    printf("full numerator:\n ");
    print255(numerator);
    printf("full denominator:\n ");
    print255(denominator);
    #endif
    while (quotient_tail >= quotient) {
        *quotient_tail = 0;
        int divider = unsafe_largest_int_multiple_and_subtract255(partial, remainder--, denominator, len_denominator);
        if (divider)
            unsafe255_add_int(quotient_tail--, divider);
        else
            --quotient_tail;
    }
    free255(partial);
    return quotient;
}
