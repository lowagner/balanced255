#include "balanced255.h"
#include "allocate255.h"

#define TEST(x) \
    if (test_##x()) { \
        printf("test_"#x" failed\n\n"); return 1; \
    } else \
        printf("test_"#x" passed\n\n");

#define TESTSHOULDFAIL(x) \
    if (test_##x()) \
        printf("test_"#x" failed, which means it passed. (it was supposed to fail.)\n\n"); \
    else { \
        printf("test_"#x" passed, which means it failed.  it should have failed.\n\n"); return 1;\
    }

int test_new255() {
    int value = 1234;
    balanced255 x = new255(value);
    printf("internal representation of x, should be equal to %d:\n ", value);
    print255(x);
    long long int result = value255(x);
    printf("recalculated result: %lld\n", result);
    free255(x);
    if (result != value)
        return 1;
    return 0;
}

int test_compare_equal255() {
    int value1 = 1234;
    int value2 = 1234;
    balanced255 x1 = new255(value1);
    printf("internal representation of x1, should be equal to %d:\n ", value1);
    print255(x1);
    balanced255 x2 = new255(value2);
    printf("internal representation of x2, should be equal to %d:\n ", value2);
    print255(x2);
    int result = compare255(x1, x2);
    free255(x2);
    free255(x1);
    if (result != 0)
        return 1;
    return 0;
}

int test_compare_less255() {
    int value1 = -1234;
    int value2 = 1234;
    balanced255 x1 = new255(value1);
    printf("internal representation of x1, should be equal to %d:\n ", value1);
    print255(x1);
    balanced255 x2 = new255(value2);
    printf("internal representation of x2, should be equal to %d:\n ", value2);
    print255(x2);
    int result = compare255(x1, x2);
    free255(x2);
    free255(x1);
    if (result != -1)
        return 1;
    return 0;
}

int test_compare_another_less255() {
    int value1 = -6293455;
    int value2 = 1234;
    balanced255 x1 = new255(value1);
    printf("internal representation of x1, should be equal to %d:\n ", value1);
    print255(x1);
    balanced255 x2 = new255(value2);
    printf("internal representation of x2, should be equal to %d:\n ", value2);
    print255(x2);
    int result = compare255(x1, x2);
    free255(x2);
    free255(x1);
    if (result != -1)
        return 1;
    return 0;
}

int test_compare_more255() {
    int value1 = 100234;
    int value2 = 14;
    balanced255 x1 = new255(value1);
    printf("internal representation of x1, should be equal to %d:\n ", value1);
    print255(x1);
    balanced255 x2 = new255(value2);
    printf("internal representation of x2, should be equal to %d:\n ", value2);
    print255(x2);
    int result = compare255(x1, x2);
    free255(x2);
    free255(x1);
    if (result != 1)
        return 1;
    return 0;
}

int test_abs_compare255() {
    int value1 = -100234;
    int value2 = 100234;
    balanced255 x1 = new255(value1);
    printf("internal representation of x1, should be equal to %d:\n ", value1);
    print255(x1);
    balanced255 x2 = new255(value2);
    printf("internal representation of x2, should be equal to %d:\n ", value2);
    print255(x2);
    int result = abs_compare255(x1, x2);
    free255(x2);
    free255(x1);
    if (result != 0)
        return 1;
    return 0;
}

int test_same_sign_abs_compare255() {
    int value1 = 100234;
    int value2 = 500234;
    balanced255 x1 = new255(value1);
    printf("internal representation of x1, should be equal to %d:\n ", value1);
    print255(x1);
    balanced255 x2 = new255(value2);
    printf("internal representation of x2, should be equal to %d:\n ", value2);
    print255(x2);
    int result = abs_compare255(x1, x2);
    free255(x2);
    free255(x1);
    if (result != -1)
        return 1;
    return 0;
}

int test_another_abs_compare255() {
    balanced255 x1 = allocate255(4);
    balanced255 x2 = allocate255(4);
    x1[0] = 0;
    x1[1] = 55;
    x1[2] = 5;
    x1[3] = -128;
    x2[0] = 0;
    x2[1] = 45;
    x2[2] = -5;
    x2[3] = -128;
    int value1 = value255(x1);
    int value2 = value255(x2);
    printf("internal representation of x1, should be equal to %d:\n ", value1);
    print255(x1);
    printf("internal representation of x2, should be equal to %d:\n ", value2);
    print255(x2);
    int result = abs_compare255(x1, x2);
    free255(x2);
    free255(x1);
    if (result != 1)
        return 1;
    return 0;
}

int test_third_abs_compare255() {
    balanced255 x1 = allocate255(4);
    balanced255 x2 = allocate255(4);
    x1[0] = 0;
    x1[1] = 55;
    x1[2] = 5;
    x1[3] = -128;
    x2[0] = 0;
    x2[1] = -45;
    x2[2] = -5;
    x2[3] = -128;
    int value1 = value255(x1);
    int value2 = value255(x2);
    printf("internal representation of x1, should be equal to %d:\n ", value1);
    print255(x1);
    printf("internal representation of x2, should be equal to %d:\n ", value2);
    print255(x2);
    int result = abs_compare255(x1, x2);
    free255(x2);
    free255(x1);
    if (result != 1)
        return 1;
    return 0;
}

int test_add255() {
    int value1 = 110001;
    int value2 = -5342159;
    balanced255 x1 = new255(value1);
    printf("internal representation of x1, should be equal to %d:\n ", value1);
    print255(x1);
    balanced255 x2 = new255(value2);
    printf("internal representation of x2, should be equal to %d:\n ", value2);
    print255(x2);
    balanced255 x3 = add255(x1, x2);
    long long int result = value255(x3);
    printf("internal representation of x3 = x1+x2, should be equal to %d:\n ", value1+value2);
    print255(x3);
    printf("recalculated result: %lld\n", result);
    free255(x3);
    free255(x2);
    free255(x1);
    if (result != value1+value2)
        return 1;
    return 0;
}

int test_subtract255() {
    int value1 = 33401;
    int value2 = 5306987;
    balanced255 x1 = new255(value1);
    printf("internal representation of x1, should be equal to %d:\n ", value1);
    print255(x1);
    balanced255 x2 = new255(value2);
    printf("internal representation of x2, should be equal to %d:\n ", value2);
    print255(x2);
    balanced255 x3 = subtract255(x1, x2);
    long long int result = value255(x3);
    printf("internal representation of x3 = x1-x2, should be equal to %d:\n ", value1-value2);
    print255(x3);
    printf("recalculated result: %lld\n", result);
    free255(x3);
    free255(x2);
    free255(x1);
    if (result != value1-value2)
        return 1;
    return 0;
}

int test_nonzero255() {
    balanced255 x = new255(-12534234);
    int result = is_nonzero255(x); 
    print255(x);
    free255(x);
    if (result == 0)
        return 1;
    return 0;
}

int test_zero255() {
    balanced255 x = new255(0);
    int result = is_zero255(x); 
    print255(x);
    free255(x);
    if (result == 0)
        return 1;
    return 0;
}

int test_add_to_zero255() {
    balanced255 x1 = new255(-12030);
    balanced255 x2 = new255( 12030);
    printf("internal representation of x1:\n ");
    print255(x1);
    printf("internal representation of x2:\n ");
    print255(x2);
    balanced255 x3 = add255(x1, x2);
    printf("internal representation of x3 = x1+x2:\n ");
    print255(x3);
    int result = is_zero255(x3);
    free255(x3);
    free255(x2);
    free255(x1);
    if (result == 0)
        return 1;
    return 0;
}

int test_allocation255() {
    balanced255 x = new255(128);
    printf("internal representation of x:\n ");
    print255(x);
    int length = length255(x);
    free255(x);
    if (length != 3)
        return 1;
    return 0;
}

int test_decrement255() {
    balanced255 x = new255(-8290687);
    printf("internal representation of x:\n ");
    print255(x);
    decrement255(&x);
    printf("internal representation of x after decrement:\n ");
    print255(x);
    long long int value = value255(x);
    free255(x);
    if (value != -8290688)
        return 1;
    return 0;
}

int test_increment255() {
    balanced255 x = new255(127);
    printf("internal representation of x:\n ");
    print255(x);
    increment255(&x);
    printf("internal representation of x after increment:\n ");
    print255(x);
    long long int value = value255(x);
    free255(x);
    if (value != 128)
        return 1;
    return 0;
}

int test_zero_increment255() {
    balanced255 x = new255(0);
    printf("internal representation of x:\n ");
    print255(x);
    increment255(&x);
    printf("internal representation of x after increment:\n ");
    print255(x);
    long long int value = value255(x);
    free255(x);
    if (value != 1)
        return 1;
    return 0;
}

int test_equality255() {
    balanced255 x = new255(1005);
    balanced255 y1 = new255(1000);
    balanced255 y2 = new255(5);
    balanced255 y = add255(y1, y2);
    int result = are_equal255(x, y);
    free255(y);
    free255(y2);
    free255(y1);
    free255(x);
    if (result != 1)
        return 1;
    return 0;
}

int test_multiply255() {
    int value1 = -510;
    int value2 = 150517;
    balanced255 x1 = new255(value1);
    printf("internal representation of x1:\n ");
    print255(x1);
    balanced255 x2 = new255(value2);
    printf("internal representation of x2:\n ");
    print255(x2);
    printf("internal representation of balanced255(value1*value2):\n ");
    balanced255 x3 = new255(value1*value2);
    print255(x3);
    printf("internal representation of x1*x2:\n ");
    balanced255 x4 = multiply255(x1, x2);
    print255(x4);
    int result = are_equal255(x3, x4);
    free255(x4);
    free255(x3);
    free255(x2);
    free255(x1);
    if (result == 0)
        return 1;
    return 0;
}

int test_another_multiply255() {
    int value1 = -128;
    int value2 = 100;
    balanced255 x1 = new255(value1);
    increment255(&x1); ++value1;
    printf("initial internal representation of x1:\n ");
    print255(x1);
    balanced255 x2 = new255(value2);
    printf("internal representation of x2:\n ");
    print255(x2);
    printf("internal representation of balanced255(value1*value2):\n ");
    balanced255 x3 = new255(value1*value2);
    print255(x3);
    printf("internal representation of x1*x2:\n ");
    balanced255 x4 = multiply255(x1, x2);
    print255(x4);
    int result = are_equal255(x3, x4);
    free255(x4);
    free255(x3);
    free255(x2);
    free255(x1);
    if (result == 0)
        return 1;
    return 0;
}

int test_drop_tail255() {
    balanced255 x1 = allocate255(4);
    balanced255 x2 = allocate255(4);
    x1[0] = 0;
    x1[1] = -55;
    x1[2] = 5;
    x1[3] = -128;
    x2[0] = 0;
    x2[1] = 0;
    x2[2] = 0;
    x2[3] = -128;
    int value1 = value255(x1);
    int value2 = value255(x2);
    printf("initial internal representation of x1 = %d:\n ", value1);
    print255(x1);
    printf("internal representation of x2 = %d:\n ", value2);
    print255(x2);
    printf("checking for zero: %d\n", length255(x2));
    print255(x2);
    printf("internal representation of balanced255(value1*value2):\n ");
    balanced255 x3 = new255(value1*value2);
    print255(x3);
    printf("internal representation of x1*x2:\n ");
    balanced255 x4 = multiply255(x1, x2);
    print255(x4);
    int result = are_equal255(x3, x4);
    free255(x4);
    free255(x3);
    free255(x2);
    free255(x1);
    if (result == 0)
        return 1;
    return 0;
}

int test_divide255() {
    balanced255 N = allocate255(7);
    N[0] = 127;
    N[1] = 0;
    N[2] = -100;
    N[3] = 10;
    N[4] = 0;
    N[5] = 5;
    N[6] = -128;
    balanced255 D = allocate255(4);
    D[0] = 15;
    D[1] = 0;
    D[2] = 2;
    D[3] = -128;
    printf("initial internal representation of N = 5391178858252:\n ");
    print255(N);
    printf("internal representation of D = 130065:\n ");
    print255(D);
    balanced255 Q = quotient_remainder255(N, D);
    printf("internal representation of quotient (N/D) = 41449881:\n ");
    print255(Q);
    int value_Q = value255(Q);
    printf("internal representation of remainder (N%%D) = 85987:\n ");
    print255(N);
    int value_R = value255(N);
    free255(Q);
    free255(D);
    free255(N);
    if (value_Q != 41449881 || value_R != 85987) {
        fprintf(stderr, "incorrect value(s) for remainder or quotient\n");
        return 1;
    }
    return 0;
}

int test_another_divide255() {
    balanced255 N = allocate255(4);
    N[0] = 113;
    N[1] = -100;
    N[2] = 43;
    N[3] = -128;
    balanced255 D = allocate255(3);
    D[0] = -10;
    D[1] = 10;
    D[2] = -128;
    int value_N = value255(N);
    int value_D = value255(D);
    printf("initial internal representation of N = %d:\n ", value_N);
    print255(N);
    printf("internal representation of D = %d:\n ", value_D);
    print255(D);
    balanced255 Q = quotient_remainder255(N, D);
    printf("internal representation of quotient (N/D) = %d:\n ", value_N/value_D);
    print255(Q);
    int value_Q = value255(Q);
    printf("internal representation of remainder (N%%D) = %d:\n ", value_N%value_D);
    print255(N);
    int value_R = value255(N);
    free255(Q);
    free255(D);
    free255(N);
    if (value_Q != value_N/value_D || value_R != value_N%value_D) {
        fprintf(stderr, "incorrect value(s) for remainder or quotient\n");
        return 1;
    }
    return 0;
}

int test_many255() {
    for (int i=-1000; i<100000; ++i) {
        for (int j=-10000; j<10000005; ++j) {
            balanced255 N = new255(i); 
            balanced255 D = new255(j); 
            balanced255 R = copy255(N);
            balanced255 Q = quotient_remainder255(R, D);
            balanced255 X = multiply255(Q, D); // multiply quotient and divider
            balanced255 S = add255(X, R); // add remainder
            if (compare255(N, S)) {
                fprintf(stderr, "failed to recombine quotient and remainder into numerator\n");
                fprintf(stderr, "N = %d, D = %d, got %lld rem %lld\n", i, j, value255(Q), value255(R));
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

int test_print_decimal255() {
    int value = 12342342;
    printf("value is %d\n", value);
    balanced255 a = new255(value);
    fprinting255_as_decimal(stdout, a);
    free255(a);
    return 0;
}

int main(int narg, char **args) {
    TEST(new255);
    TEST(compare_equal255);
    TEST(compare_less255);
    TEST(compare_another_less255);
    TEST(compare_more255);
    TEST(abs_compare255);
    TEST(same_sign_abs_compare255);
    TEST(another_abs_compare255);
    TEST(third_abs_compare255);
    TEST(add255);
    TEST(subtract255);
    TEST(nonzero255);
    TEST(zero255);
    TEST(add_to_zero255);
    TEST(allocation255);
    TEST(decrement255);
    TEST(increment255);
    TEST(zero_increment255);
    TEST(equality255);
    TEST(multiply255);
    TEST(another_multiply255);
    TEST(drop_tail255);
    TEST(print_decimal255);
    TEST(divide255);
    TEST(another_divide255);
    TEST(many255);
    printf("all tests passed, good work and go home.\n");
    return 0;
}

