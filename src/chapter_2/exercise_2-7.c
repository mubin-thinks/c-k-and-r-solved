#include <stdio.h>

unsigned int invert(unsigned int x, int p, int n);
void print_bits(unsigned int x, int count);
void print_test(unsigned int x, int p, int n);

int main() {
        printf("invert(                 x,  p,  n) = result\n");
        printf("-------------------------------------------\n");
        print_test(0b01110001, 5, 4);
        print_test(0b11111111, 2, 3);
        print_test(0b11111111, 7, 8);
        print_test(0b11000001, 5, 5);
        print_test(0b01110001, 7, 8);
        print_test(0b00000000, 7, 1);
        print_test(0b11111111, 7, 0);
        return 0;
}

unsigned int invert(unsigned int x, int p, int n) {
        if (!n) return x;
        unsigned int y = ((2 << (n - 1)) - 1) << (p - n + 1);
        return (x & ~y) | (~x & y);
}

void print_bits(unsigned int x, int count) {
        for (; count; ) printf("%u", (x >> (--count)) & 1);
}

void print_test(unsigned int x, int p, int n) {
        printf("invert(0b");
        print_bits(x, 16);
        printf(", %2d, %2d) = 0b", p, n);
        print_bits(invert(x, p, n), 16);
        putchar('\n');
}
