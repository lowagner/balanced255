# balanced255
inspired by an [esoteric programming language](http://www.dangermouse.net/esoteric/bit.html), 
every number is (like) a C-string

## balanced ternary is cool, but

balanced 255 is even better.  internally, a balanced255 number is a sequence of signed bytes (`int8_t`),
which terminates when a -128-valued byte is found.  (-128 shouldn't appear in a balanced 255 number.)
all other values -127 to 127 are possible as "digits" and contribute to the total value of the number.

consider such a sequence:

    [0, 5, -1, -128]

using little-endian ordering, this has the numeric value `0*1 + 5*255 + -1*(255*255) = -63750`.

## balanced255 code features

* manual memory management:  if you create a balanced255 number via any of the following functions:
```
    balanced255 new255(int initial_value)
    balanced255 add255(balanced255 a, balanced255 b)
    balanced255 copy255(balanced255 a)
```

you will need to free it when you are done using it via 
```
    void free255(balanced255 c)
```

_for this reason, you should never use `new255` for a temporary balanced255 inside an argument._

* check zero/nonzero:  
```
    int is_zero255(balanced255 x)
    int is_nonzero255(balanced255 x)
```

* determine sign:  in general, balanced numbers are positive or negative based on
the positivity/negativity of their most significant digit, which is what these functions check:
```
    int is_positive255(balanced255 x)
    int is_negative255(balanced255 x)
```

* increment/decrement: 
```
    void increment255(balanced255 x)
    void decrement255(balanced255 x)
```

* determine the length of the array which makes up the balanced255 number:
```
    int length255(balanced255 x)
```

* and of course you can print the array at any time, or print to file:
```
    void print255(balanced255 x)
    void fprint255(FILE *f, balanced255 x)
```


## TODO

* fast multiplication for larger numbers?
* \*= algorithm
* print\_decimal255 for very large numbers
