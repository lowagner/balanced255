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

void fprinting255_as_decimal(FILE *f, balanced255 a0) {
    // a0 + B a1 + B^2 a2 + B^3 a3 + ...
    if (is_zero255(a0)) {
        fprintf(f, "0");
        return;
    } 
    // use long division with remainders.
    int max_length = length255(a0);
    int *base10000 = (int*)calloc(max_length, sizeof(int));
    balanced255 ten_thousand = new255(10000);
    balanced255 a = copy255(a0);
    if (is_negative255(a)) {
        negate255(a);
        fprintf(f, "-");
    }
    int max_index = -1;
    while (1) {
        balanced255 q = quotient_remainder255(a, ten_thousand);
        base10000[++max_index] = value255(a);
        free255(a);
        a = q;
        if (length255(a) == 1)
            break;
    }
    free255(a);
    free255(ten_thousand);
    char buffer[5];
    buffer[0] = '0' + base10000[max_index]/1000;
    buffer[1] = '0' + (base10000[max_index]/100)%10;
    buffer[2] = '0' + (base10000[max_index]/10)%10;
    buffer[3] = '0' + base10000[max_index]%10;
    buffer[4] = 0;
    {
        // don't write leading zeros
        char *b = buffer;
        while (*b == '0') {
            ++b;
        }
        fprintf(f, "%s", b);
    }
    while (--max_index >= 0) {
        buffer[0] = '0' + base10000[max_index]/1000;
        buffer[1] = '0' + (base10000[max_index]/100)%10;
        buffer[2] = '0' + (base10000[max_index]/10)%10;
        buffer[3] = '0' + base10000[max_index]%10;
        fprintf(f, "%s", buffer);
    }
    free(base10000);
}

void fprint255_as_decimal(FILE *f, balanced255 a) {
    fprinting255_as_decimal(f, a);
    fprintf(f, "\n");
}

void printing255_as_decimal(balanced255 a) {
    fprinting255_as_decimal(stdout, a);
}

void print255_as_decimal(balanced255 a) {
    fprinting255_as_decimal(stdout, a);
    fprintf(stdout, "\n");
}
