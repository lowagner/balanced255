#include "balanced255.h"
#include "allocate255.h"

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


balanced255 add255(balanced255 a, balanced255 b) {
    int alloc;
    {
        const int len_a = length255(a);
        const int len_b = length255(b);
        if (len_a > len_b) {
            if (len_b <= 1)
                return copy255(a);
            alloc = len_a + 1;
        } else {
            if (len_b <= 1)
                return copy255(a);
            alloc = len_b + 1;
        }
    }
    balanced255 head = allocate255(alloc);
    int8_t *tail = head;
    int carry = 0;
    while (1) {
        if (*b == -128)
            break;
        else if (*a == -128) {
            a = b; // could swap, but we don't consider b any further below
            break;
        }
        carry += (int8_t)(*a++) + (int8_t)(*b++); 
        *tail++ = carry_next_digit255(&carry);
    }
    // finish adding a to the vector, b is done for
    while (*a != -128) {
        carry += (int8_t)(*a++); 
        *tail++ = carry_next_digit255(&carry);
    }
    while (carry) { // one final piece
        #if DEBUG > 9000
        printf("final carry %d, should only happen once...\n", carry);
        #endif
        *tail++ = carry_next_digit255(&carry);
    }
    *tail = -128;
    clean255(head, tail);
    return head;
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

