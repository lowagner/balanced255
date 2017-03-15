#include "balanced255.h"
#include "allocate255.h"

#define TEST(x) \
    if (test_##x()) { \
        printf("test_"#x" failed\n\n"); return 1; \
    } else \
        printf("test_"#x" passed\n\n");

int test_many255() {
    for (int i=-10; i<10000; ++i) {
        for (int j=-abs(i)-1; j<abs(i)+1; ++j) {
            fprintf(stderr, "N = %d, D = %d,\n", i, j);
            balanced255 N = new255(i); 
            balanced255 D = new255(j); 
            balanced255 R = copy255(N);
            balanced255 Q = quotient_remainder255(R, D);
            balanced255 X = multiply255(Q, D); // multiply quotient and divider
            balanced255 S = add255(X, R); // add remainder
            fprintf(stderr, "got %lld rem %lld\n", value255(Q), value255(R));
            if (j != 0 && compare255(N, S)) {
                fprintf(stderr, "failed to recombine quotient and remainder into numerator\n");
                fprinting255(stderr, N); 
                fprintf(stderr, " != ");
                fprinting255(stderr, Q); 
                fprinting255(stderr, D); 
                fprintf(stderr, " + ");
                fprinting255(stderr, R); 
                fprintf(stderr, "; got ");
                fprint255(stderr, S); 
            
                free255(S);
                free255(X);
                free255(Q);
                free255(R);
                free255(D);
                free255(N);
                return 1;
            }
            free255(S);
            free255(X);
            free255(Q);
            free255(R);
            free255(D);
            free255(N);
        }
    }
    return 0;
}

int main(int narg, char **args) {
    TEST(many255);
    printf("all tests passed, good work and go home.\n");
    return 0;
}

