#include "balanced255.h"
#include <stdlib.h> // malloc
#include <string.h> // memcpy

void fprinting255(FILE *f, balanced255 a) {
    fprintf(f, "[%d", (int)*a);
    while (*a != -128)
        fprintf(f, ", %d", (int)*++a); 
    fprintf(f, "]");
}

void fprint255(FILE *f, balanced255 a) {
    fprinting255(f, a);
    fprintf(f, "\n");
}

void printing255(balanced255 a) {
    fprinting255(stdout, a);
}

void print255(balanced255 a) {
    fprinting255(stdout, a);
    printf("\n");
}

int length255(balanced255 a) {
    int count=1; // include the -128 byte as part of the length.
    while (*a++ != -128)
        ++count;
    return count;
}

long long int value255(balanced255 a) {
    if (*a == -128)
        return 0;
    long long int power = 1;
    long long int value = (int8_t)*a++;
    while (*a != -128) {
        power *= 255;
        value += power*(*a++);
    }
    return value;
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

static inline int8_t carry_next_digit255(int *carry) {
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

balanced255 new255(int k) {
    int carry = k;
    int alloc;
    if (k == 0)
        alloc = 2;
    else {
        alloc = 1;
        while (k) {
            ++alloc;
            carry_next_digit255(&k);
        }
    }
    balanced255 head = allocate255(alloc); 
    int8_t *tail = head;
    while (carry)
        *tail++ = carry_next_digit255(&carry);
    *tail = -128;
    #if DEBUG > 9000
    fprintf(stderr, "used/allocated = %d/%d\n", length255(head), alloc);
    #endif
    return head;
}

static inline void clean255(balanced255 head, balanced255 tail) {
    #if DEBUG > 9000
    if (*tail != -128) {
        fprintf(stderr, "not starting at the tail of the balanced255 number\n");
        return;
    }
    #endif
    while (--tail >= head) {
        if (*tail == 0)
            *tail = -128;
        else
            break;
    }
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
    if (*a == -128) {
        // a was zero, but we have two bytes to work with (see new255)
        *a = 1;
        *++a = -128;
        return;
    }
    // worst case cascade will require a realloc
    //  127  127  127  127  127 -128
    // -127 -127 -127 -127 -127 1   -128
    int alloc=2; 
    do {
        if (++(*a) != -128) 
            return;
        *a++ = -127;
        ++alloc;
    } while ((*a) != -128);
    
    // need to reallocate here.
    a = reallocate255(aptr, alloc); // value of aptr could be different after reallocation
    a[alloc-2] = 1;
    a[alloc-1] = -128;
}

void decrement255(balanced255 *aptr) {
    balanced255 a = *aptr;
    if (*a == -128) {
        // a was zero, we always have two bytes to work with (see new255)
        *a = -1;
        *++a = -128;
        return;
    } 

    // worst case cascade will require a realloc
    // -127 -127 -127 -127 -127 -128
    //  127  127  127  127  127 -1 -128
    int alloc=2; 
    do {
        if (--(*a) != -128) 
            return;
        *a++ = 127;
        ++alloc;
    } while ((*a) != -128);
    
    // need to reallocate here.
    a = reallocate255(aptr, alloc); // value of aptr could be different after reallocation
    a[alloc-2] = -1;
    a[alloc-1] = -128;
}

balanced255 copy255(balanced255 a) {
    int len_a = length255(a);
    balanced255 result = allocate255(len_a);
    memcpy(result, a, len_a*sizeof(int8_t));
}

balanced255 allocate255(int length) {
    #if DEBUG > 9000
    printf("allocating %d for balanced255 number\n", length);
    #endif
    return (balanced255)malloc(length*sizeof(int8_t));
}

balanced255 reallocate255(balanced255 *a, int length) {
    #if DEBUG > 9000
    printf("reallocating %d for balanced255 number\n", length);
    #endif
    *a = realloc(*a, length*sizeof(int8_t));
    return *a;
}

void free255(balanced255 a) {
    free(a);
}
