#include <stdio.h>

unsigned int rightrot(unsigned int x, int n);
void print_bits(unsigned int x, int count);
void print_test(unsigned int x, int n);

int main() {
        printf("rightrot(                 x,  n) = result\n");
        printf("-----------------------------------------\n");
        print_test(0b01110001, 4);
        print_test(0b11111111, 3);
        print_test(0b11111111, 8);
        print_test(0b11000001, 5);
        print_test(0b01110001, 8);
        print_test(0b00000000, 1);
        print_test(0b11111111, 0);
        return 0;
}

// Unsigned int in most modern computers usually contain
// 32bits. Therefore, right rotation will rotate the
// rightmost n bits to very left of 32bits.
unsigned int rightrot(unsigned int x, int n) {
        unsigned int y = x & ((1 << n) - 1);
        return (x >> n) | (y << (32 - n));
}

void print_bits(unsigned int x, int count) {
        for (; count; ) printf("%u", (x >> (--count)) & 1);
}

void print_test(unsigned int x, int n) {
        printf("rightrot(0b");
        print_bits(x, 16);
        printf(", %2d) = 0b", n);
        print_bits(rightrot(x, n), 32);
        putchar('\n');
}
