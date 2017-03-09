#include "balanced255.h"
#include "allocate255.h"
#include "unsafe255.h"
#include <string.h> // memcpy
#include <stdlib.h> // free

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

balanced255 new255(int k) {
    int carry = k;
    int alloc = 1;
    while (k) {
        ++alloc;
        carry_next_digit255(&k);
    }
    balanced255 a = allocate255(alloc); 
    unsafe255_from_int(a, carry);
    return a;
}

balanced255 copy255(balanced255 a) {
    int len_a = length255(a);
    balanced255 result = allocate255(len_a);
    memcpy(result, a, len_a*sizeof(int8_t));
}

void free255(balanced255 a) {
    free(a);
}
