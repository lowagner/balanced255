# balanced255
inspired by an [esoteric programming language](http://www.dangermouse.net/esoteric/bit.html), 
every number is (like) a C-string

## balanced ternary is cool, but

balanced 255 is even better.  internally, a balanced255 number is a sequence of signed bytes (`int8_t`),
which terminates when a -128-valued byte is found.  (-128 shouldn't appear in a balanced 255 number.)
all other values -127 to 127 are possible and contribute to the total value of the number.

consider such a sequence:

    [0, 5, -1, -128]

using little-endian ordering, this has the numeric value `0*1 + 5*255 + -1*(255*255) = -63750`.
