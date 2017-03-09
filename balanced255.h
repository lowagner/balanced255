#pragma once
#include "config.h"
#include <stdio.h>

typedef int8_t *balanced255;

void fprinting255(FILE *f, balanced255 a);
void fprint255(FILE *f, balanced255 a);
void printing255(balanced255 a);
void print255(balanced255 a);

int length255(balanced255 a);
long long int value255(balanced255 a);

int is_zero255(balanced255 a);
int is_nonzero255(balanced255 a);
int is_positive255(balanced255 a);
int is_negative255(balanced255 a);

void increment255(balanced255 *aptr);
void decrement255(balanced255 *aptr);

balanced255 new255(int k);
balanced255 add255(balanced255 a, balanced255 b);

balanced255 copy255(balanced255 a);
balanced255 allocate255(int length);
balanced255 reallocate255(balanced255 *a, int length);
void free255(balanced255 a);
