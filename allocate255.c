#include "balanced255.h"
#include <stdlib.h> // malloc
#include <string.h> // free

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

void clean255(balanced255 head, balanced255 tail) {
    // clear trailing zeroes
    // TODO: realloc?
    #if DEBUG > 9000
    if (*tail != -128) {
        fprintf(stderr, "not starting at the tail of the balanced255 number\n");
        return;
    }
    #endif
    while (--tail > head)
    {
        if (*tail != 0) {
            *(tail+1) = -128;
            break;
        }
    }
}
