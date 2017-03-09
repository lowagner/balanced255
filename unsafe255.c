#include "balanced255.h"

void unsafe255_from_int(balanced255 a, int carry) {
    // a is zero, add carry.  a should be preallocated.
    while (carry)
        *a++ = carry_next_digit255(&carry);
    *a = -128;
}

void unsafe255_add_int(balanced255 a, int carry) {
    // a is nonzero, add carry.  a should be preallocated.
    while (carry) {
        carry += (int8_t)*a;
        *a++ = carry_next_digit255(&carry);
    }
    *a = -128;
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
