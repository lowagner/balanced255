#include "balanced255.h"
#include <stdlib.h>

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

void fprinting255_as_decimal(FILE *f, balanced255 a) {
    // a0 + B a1 + B^2 a2 + B^3 a3 + ...
    if (is_zero255(a)) {
        fprintf(f, "0");
        return;
    } 
    /* TODO: long division with remainders?
    int *base1000 = (int*)calloc(length255(a), sizeof(int));

    balanced255 tail = a;
    int power_mod1000 = 1;
    base1000[0] = *tail;
    while (*++tail != -128) {
        power_mod1000 = (power_mod1000*255)%1000;
        base1000[0] = (base1000[0] + (power_mod1000*(*tail))%1000)%1000;
    }
    fprintf(f, "hello 1000's \"digit\": %d\n", base1000[0]);
    */
}
