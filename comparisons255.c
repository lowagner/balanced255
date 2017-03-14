#include "balanced255.h"

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

int are_equal255(balanced255 a, balanced255 b) {
    while (1) {
        if (*a == -128)
            return is_zero255(b);
        if (*b == -128)
            return is_zero255(a);
        if (*a++ != *b++)
            return 0;
    }
}

int compare255(balanced255 a, balanced255 b) {
    // return 0 if a==b, -1 if a<b, and +1 if a>b
    int len_a = length255(a);
    int len_b = length255(b);
    if (len_a == 1) {
        if (len_b == 1)
            return 0;
        // a is zero, b is not zero
        // if b is negative, return 1, otherwise return -1
        return -1 + 2*is_negative255(b);
    } else if (len_b == 1) {
        // a is nonzero, b is zero
        return -1 + 2*is_positive255(a);
    }
    // otherwise: len_a > 1 and len_b > 1
    balanced255 a_tail = a + len_a - 2;
    balanced255 b_tail = b + len_b - 2;
    if (len_a == len_b) {
        // same size integers; look at most significant bits, find first difference
        while (a_tail >= a) {
            if (*a_tail < *b_tail)
                return -1;
            else if (*a_tail > *b_tail)
                return 1;
            --a_tail;
            --b_tail;
        }
        return 0;
    } else if (len_a > len_b) {
        // a is larger in magnitude than b
        if (*a_tail < 0)  // a is negative
            return -1; // a is more negative than b (if b is negative); also a < b if b is positive
        // else a is positive
        return 1;
    }
    // b is larger in magnitude than a
    if (*b_tail < 0)  // b is negative
        return 1; // b is more negative than a (if a is negative); also b < a if a is positive
    return -1; // b is positive
}

int abs_compare255(balanced255 a, balanced255 b) {
    // return 0 if |a|==|b|, -1 if |a|<|b|, and +1 if |a|>|b|
    int len_a = length255(a);
    int len_b = length255(b);
    if (len_a == len_b) {
        if (len_a == 1)
            return 0; // both are zero
        // same size integers; look at most significant bits, find first difference
        balanced255 a_tail = a + len_a - 2;
        balanced255 b_tail = b + len_b - 2;
        int a_sign = 0;
        int b_sign = 0;
        int abs_a = abs(*a_tail);
        int abs_b = abs(*b_tail);
        if (abs_a == abs_b) {
            a_sign = (*a_tail < 0) ? -1 : 1;
            b_sign = (*b_tail < 0) ? -1 : 1;
        } else if (abs_a < abs_b)
            return -1;
        else
            return 1;
        #if DEBUG > 9000
        fprintf(stderr, "in abs_compare255\n");
        fprintf(stderr, "sign a, b = %d, %d\n", a_sign, b_sign);
        #endif
        
        while (--a_tail, --b_tail, a_tail >= a) {
            abs_a = *a_tail*a_sign;
            abs_b = *b_tail*b_sign;
            if (abs_a == abs_b)
                continue;
            else if (abs_a < abs_b)
                return -1;
            else
                return 1;
        }
        return 0;
    } else if (len_a > len_b) {
        // a is larger in magnitude than b
        return 1;
    }
    // b is larger in magnitude than a
    return -1;
}

