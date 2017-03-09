#include "balanced255.h"
#include "allocate255.h"
#include "unsafe255.h"

int is_zero255(balanced255 a) {
    while (*a != -128) {
        if (*a++ != 0)
            return 0;
    }
    return 1;
}

int is_nonzero255(balanced255 a) {
    while (*a != -128) {
        if (*a++ != 0)
            return 1;
    }
    return 0;
}

int is_positive255(balanced255 a) {
    if (*a == -128)
        return 0;
    while (*(a+1) != -128)
        ++a;
    return (*a) > 0;
}

int is_negative255(balanced255 a) {
    if (*a == -128)
        return 0;
    while (*(a+1) != -128)
        ++a;
    return (*a) < 0;
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

