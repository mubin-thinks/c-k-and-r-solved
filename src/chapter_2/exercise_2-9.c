// Most modern computers use 2's compliment to represent
// negative values.
//
// In the statement x &= (x - 1), the expression x - 1 can
// be written like this: x + (-1)
//
// To view an example on why x &= (x - 1) *always* removes
// the rightmost set bit, we will be padding every number to
// 8 bits.
//
// -1 in 2's compliment can be represented as follows:
//
//        decimal 1                = 00000001
//        (1's compliment)         = 11111110
//                                  +       1
//        -----------------------------------
//        (2's compliment i.e. -1) = 11111111
//
// From this observation, we can confirm that -1 is always
// ~0 in 2's as all bits accept the rightmost will be 1 in
// 1's compliment. After which, we add 1. Therefore, all
// bits will be 1.
//
// As an example let x = 74, which is 01001010 in binary.
// so the expression x + (-1) becomes:
//
//         01001010 (x)
//        +11111111 (-1 or ~0)
//        ---------
//        101001001
//        🠙
//        └─── overflow bit (we do not consider)
//
// We can see the rightmost 1+1 will be 0 and all 1+1 on the
// left will be 1 and 0+1 will be 0 and all 0s right of
// the rightmost 1 will become 1 because of 0+1.
//
// This is because there will be the start of carry from
// the rightmost 1+1 but itself will not have any carry and
// the result of the rightmost 1+1 will be 0.
//
// Now, x &= (x - 1); should make sense, we just & the
// result with x this means all the 1s right of rightmost
// 1+1 in sum will be 0 because in x, they are 0.
//
// The new x will have 0 in the place of rightmost 1+1
// because the sum was 0 for them, and all the bits left
// to it will be as is. That is because they do not change
// at all.
//
//         01001001 (x - 1)
//        &01001010 (x)
//        ---------
//         01001000
//               🠙
//               └─── 0 in place of rightmost 1

#include <stdio.h>

int bitcount(unsigned int x);

int main() {
        printf("%d\n", bitcount(0b00110100));
        printf("%d\n", bitcount(0b11111111));
        printf("%d\n", bitcount(0b00000000));
        printf("%d\n", bitcount(0b1111111100000000));
        printf("%d\n", bitcount(0b1010101010101010));
        printf("%d\n", bitcount(0b1111111111111111));
        printf("%d\n", bitcount(0b0000000000000000));
}

int bitcount(unsigned int x) {
        int result = 0;
        for (; x; x &= (x - 1), result++);
        return result;
}
