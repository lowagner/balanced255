#pragma once
#include "config255.h"

balanced255 allocate255(int length);
balanced255 reallocate255(balanced255 *a, int length);

void clean255(balanced255 head, balanced255 tail);
