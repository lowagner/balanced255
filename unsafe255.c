#include "balanced255.h"
#include "allocate255.h"
#include <string.h>

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

balanced255 unsafe_quotient_remainder255(balanced255 numerator, balanced255 denominator) {
    // denominator must not be zero, also numerator and denominator should be positive;
    if (compare255(numerator, denominator) < 0) { // a < b
        balanced255 result = allocate255(1);
        *result = -128; 
        return result;
    }
    balanced255 remainder;
    balanced255 quotient;
    balanced255 quotient_tail;
    {
        int len_numerator, len_denominator;
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
    }
    #if DEBUG > 9000
    printf("starting at numerator position (initial remainder):\n ");
    print255(remainder);
    printf("full numerator:\n ");
    print255(numerator);
    printf("full denominator:\n ");
    print255(denominator);
    #endif
    fprintf(stderr, "not implemented yet.\n");
    return quotient;
}
