#include "balanced255.h"
#include "allocate255.h"
#include "comparisons255.h"
#include "unsafe255.h"
#include <string.h>

static inline int max(int a, int b) {
    return (a > b) ? a : b;
}

int8_t carry_next_digit255(int *carry) {
    int abs_carry;
    int sign;
    if (*carry < 0) {
        abs_carry = -*carry;
        sign = -1;
    } else {
        abs_carry = *carry;
        sign = 1;
    }
    int digit = abs_carry % 255;
    abs_carry /= 255;
    if (digit > 127) {
        digit -= 255;
        ++abs_carry;
    }
    *carry = sign*abs_carry;
    return sign*digit;
}

int get_required_space_add255(balanced255 a, balanced255 b) {
    return max(length255(a), length255(b)) + 1;
}

balanced255 add255(balanced255 a, balanced255 b) {
    balanced255 head = allocate255(get_required_space_add255(a, b));
    balanced255 tail = head;
    int carry = 0;
    while (1) {
        if (*b == -128) {
            unsafe255_from255_plus_int(tail, a, carry);
            return head;
        }
        if (*a == -128) {
            unsafe255_from255_plus_int(tail, b, carry);
            return head;
        }
        carry += (int8_t)(*a++) + (int8_t)(*b++); 
        *tail++ = carry_next_digit255(&carry);
    }
}

balanced255 subtract255(balanced255 a, balanced255 b) {
    balanced255 head = allocate255(get_required_space_add255(a, b));
    balanced255 tail = head;
    int carry = 0;
    while (1) {
        if (*b == -128) {
            unsafe255_from255_plus_int(tail, a, carry);
            return head;
        }
        if (*a == -128) {
            unsafe255_from_negative255_plus_int(tail, b, carry);
            return head;
        }
        carry += (int8_t)(*a++) - (int8_t)(*b++); 
        *tail++ = carry_next_digit255(&carry);
    }
}

balanced255 negate255(balanced255 a) {
    while (*a != -128) {
        *a++ *= -1;
    }
}

void increment255(balanced255 *aptr) {
    balanced255 a = *aptr;
    // worst case cascade will require a realloc
    //  127  127  127  127  127 -128
    // -127 -127 -127 -127 -127 1   -128
    int alloc=2; 
    while ((*a) != -128) {
        if (++(*a) != -128) 
            return;
        *a++ = -127;
        ++alloc;
    }
    
    // need to reallocate here.
    a = reallocate255(aptr, alloc); // value of aptr could be different after reallocation
    a[alloc-2] = 1;
    a[alloc-1] = -128;
}

void decrement255(balanced255 *aptr) {
    balanced255 a = *aptr;
    // worst case cascade will require a realloc
    // -127 -127 -127 -127 -127 -128
    //  127  127  127  127  127 -1 -128
    int alloc=2; 
    while ((*a) != -128) {
        if (--(*a) != -128) 
            return;
        *a++ = 127;
        ++alloc;
    }
    
    // need to reallocate here.
    a = reallocate255(aptr, alloc); // value of aptr could be different after reallocation
    a[alloc-2] = -1;
    a[alloc-1] = -128;
}

int get_required_space_multiply255(balanced255 a, balanced255 b) {
    return length255(a) + length255(b);
}

balanced255 multiply255(balanced255 a, balanced255 b) {
    int result_length;
    balanced255 partial_sum;
    {
        int len_a, len_b;
        len_a = length255(a);
        len_b = length255(b);
        result_length = len_a + len_b;
        if (len_a < len_b) {
            // swap a<=>b, put the larger sized element first.
            balanced255 c = b;
            b = a;
            a = c;
            partial_sum = allocate255(len_b+1);
        } else {
            partial_sum = allocate255(len_a+1);
        }
    }
    if (is_zero255(b)) {
        balanced255 result = allocate255(1);
        *result = -128;
        return result;
    }
    balanced255 result = allocate255(result_length);
    result[0] = -128;
    unsafe255_gradeschool_multiply_nonzero255(result, partial_sum, a, b);
    return result;
}

balanced255 quotient_remainder255(balanced255 numerator, balanced255 denominator) {
    // numerator / denominator, set a equal to the remainder, and return a new balanced255 corresponding to the quotient.
    if (length255(denominator) == 2) {
        if (denominator[0] == 0) {
            fprintf(stderr, "division by zero in quotient_remainder255\n");
            balanced255 result = allocate255(1);
            *result = -128;
            *numerator = -128;
            return result;
        } else if (denominator[0] == 1) {
            balanced255 result = copy255(numerator);
            *numerator = -128;
            return result;
        } else if (denominator[0] == -1) {
            balanced255 result = negate255(copy255(numerator));
            *numerator = -128;
            return result;
        }
    }
    int negative_numerator = 0;
    if (is_negative255(numerator)) {
        negative_numerator = 1;
        negate255(numerator);
    }
    int negative_denominator = 0;
    if (is_negative255(denominator)) {
        negative_denominator = 1;
        negate255(denominator);
    }
    balanced255 quotient = unsafe_quotient_remainder255(numerator, denominator);
    // numerator is now the remainder:
    // N/D = Q rem R
    // +/+ = + rem +
    // +/- = - rem +
    // -/+ = - rem -
    // -/- = + rem -
    if (negative_numerator) {
        negate255(numerator);
        if (!negative_denominator)
            negate255(quotient);
    } else if (negative_denominator)
        negate255(quotient);
    return quotient;
}
