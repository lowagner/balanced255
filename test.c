#include "balanced255.h"

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
    balanced255 x2 = new255(value2);
    printf("internal representation of x1, should be equal to %d:\n ", value1);
    print255(x1);
    printf("internal representation of x2, should be equal to %d:\n ", value2);
    print255(x2);
    balanced255 x3 = add255(x1, x2);
    long long int result = value255(x3);
    printf("recalculated result: %lld\n", result);
    free255(x3);
    free255(x2);
    free255(x1);
    return (result != value1+value2);
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

int main(int narg, char **args) {
    TEST(new255);
    TEST(add255);
    TEST(zero255);
    TEST(add_to_zero255);
    TEST(allocation255);
    return 0;
}

