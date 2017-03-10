#include "balanced255.h"
#include "allocate255.h"

#define TEST(x) \
    if (test_##x()) { \
        printf("test_"#x" failed\n"); return 1; \
    } else \
        printf("test_"#x" passed\n");

#define TESTSHOULDFAIL(x) \
    if (test_##x()) \
        printf("test_"#x" failed, which means it passed. (it was supposed to fail.)\n"); \
    else { \
        printf("test_"#x" passed, which means it failed.  it should have failed.\n"); return 1;\
    }

int test_new255() {
    int value = 1234;
    balanced255 x = new255(value);
    printf("internal representation of x, should be equal to %d:\n ", value);
    print255(x);
    long long int result = value255(x);
    printf("recalculated result: %lld\n", result);
    free255(x);
    return (result != value);
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
    return (result != value1+value2);
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
    return (result != value1-value2);
}

int test_nonzero255() {
    balanced255 x = new255(-12534234);
    int result = is_nonzero255(x); 
    print255(x);
    free255(x);
    return (result == 0);
}

int test_zero255() {
    balanced255 x = new255(0);
    int result = is_zero255(x); 
    print255(x);
    free255(x);
    return (result == 0);
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
    return (result == 0);
}

int test_allocation255() {
    balanced255 x = new255(128);
    printf("internal representation of x:\n ");
    print255(x);
    int length = length255(x);
    free255(x);
    return (length != 3);
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
    return (value != -8290688);
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
    return (value != 128);
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
    return (value != 1);
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
    return (result != 1);
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
    return (result == 0);
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
    return (result == 0);
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
    return (result == 0);
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
    printf("all tests passed, good work and go home.\n");
    return 0;
}

