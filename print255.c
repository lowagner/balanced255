#include "balanced255.h"

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


