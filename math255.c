#include "balanced255.h"
#include "allocate255.h"
#include "unsafe255.h"
#include <string.h>

static inline int max(int a, int b) {
    if (a > b)
        return a;
    return b;
}

int compare255(balanced255 a, balanced255 b) {
    // return 0 if a==b, -1 if a<b, and +1 if a>b
    int len_a = length255(a);
    int len_b = length255(b);
    if (len_a == 1) {
        if (len_b == 1)
            return 0;
        // a is zero, b is not zero
        // if b is negative, return 1, otherwise return -1
        return -1 + 2*is_negative255(b);
    } else if (len_b == 1) {
        // a is nonzero, b is zero
        return -1 + 2*is_positive255(a);
    }
    // otherwise: len_a > 1 and len_b > 1
    balanced255 a_tail = a+len_a-1;
    balanced255 b_tail = b+len_a-1;
    if (len_a == len_b) {
        // same size integers; look at most significant bits, find first difference
        while (a_tail >= a) {
            if (*a_tail < *b_tail)
                return -1;
            else if (*a_tail > *b_tail)
                return 1;
            --a_tail;
            --b_tail;
        }
        return 0;
    } else if (len_a > len_b) {
        // a is larger in magnitude than b
        if (*a_tail < 0)  // a is negative
            return -1; // a is more negative than b (if b is negative); also a < b if b is positive
        else // a is positive
            return 1;
    }
    // b is larger in magnitude than a
    else if (*b_tail < 0)  // b is negative
        return 1; // b is more negative than a (if a is negative); also b < a if a is positive
    return -1; // b is positive
}

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

int are_equal255(balanced255 a, balanced255 b) {
    while (1) {
        if (*a == -128)
            return is_zero255(b);
        if (*b == -128)
            return is_zero255(a);
        if (*a++ != *b++)
            return 0;
    }
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
    // grade school algorithm follows...
    int head_length;
    balanced255 partial;
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
            partial = allocate255(len_b+1);
        } else {
            partial = allocate255(len_a+1);
        }
    }
    if (is_zero255(b)) {
        balanced255 result = allocate255(1);
        *result = -128;
        return result;
    }
    balanced255 head = allocate255(head_length);
    memset(head, 0, head_length*sizeof(int8_t));
    balanced255 tail = head;
    while (*b != -128) {
        #if DEBUG > 9000
        printf("multiplying in %d:\n ", (int)(*b));
        #endif
        if (*b) {
            unsafe255_multiply255_with_int(partial, a, *b);
            #if DEBUG > 9000
            printf("adding partial...\n  ");
            print255(partial);
            #endif
            unsafe255_add255(tail, partial);
        }
        ++b; 
        ++tail;
    }
    return head;
}
