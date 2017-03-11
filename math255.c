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
    int head_length;
    balanced255 partial_sum;
    {
        int len_a, len_b;
        len_a = length255(a);
        len_b = length255(b);
        head_length = len_a + len_b;
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
    balanced255 head = allocate255(head_length);
    memset(head, 0, head_length*sizeof(int8_t));
    unsafe255_gradeschool_multiply_nonzero255(head, partial_sum, a, b);
    return head;
}

balanced255 quotient_remainder255(balanced255 a, balanced255 b) {
    // a / b, set a equal to the remainder, and return a new balanced255 corresponding to the quotient.
    if (is_zero255(b)) {
        fprintf(stderr, "division by zero in quotient_remainder255\n");
        balanced255 result = allocate255(1);
        *result = -128;
        *a = -128;
        return result;
    }
    if (abs_compare255(a, b) == -1) { // |a| < |b|
        balanced255 result = allocate255(1);
        // TODO: may want to flip the sign of a, depending on sign of b and sign of a
        *result = -128; 
        return result;
    }
    int head_length;
    {
        int len_a, len_b;
        len_a = length255(a);
        len_b = length255(b);
        head_length = len_a - len_b + 2;
    }
    balanced255 head = allocate255(head_length);
    *head = -128;
    fprintf(stderr, "not implemented yet.\n");
    return head;
}
