#include <stdio.h>

unsigned int setbits(unsigned int x, int p, int n, unsigned int y);
void print_bits(unsigned int x, int count);
void print_test(unsigned int x, int p, int n, unsigned int y);

int main() {
        printf("setbits(                 x,  p,  n,                  y) = result\n");
        printf("----------------------------------------------------------------\n");
        print_test(0b01110001, 5, 4, 0b0010);
        print_test(0b11111111, 2, 3, 0b010);
        print_test(0b11111111, 7, 8, 0b000000001);
        print_test(0b11000001, 5, 5, ~0);
        print_test(0b01110001, 7, 8, ~0);
        print_test(0b00000000, 7, 1, 0b1);
        print_test(0b11111111, 7, 0, 0);
        return 0;
}

unsigned int setbits(unsigned int x, int p, int n, unsigned int y) {
        unsigned int z = (2 << (n - 1)) - 1, d = p - n + 1;
        x &= ~(z << d);
        x |= (y & z) << d;
        return x;
}

void print_bits(unsigned int x, int count) {
        for (; count; ) printf("%u", (x >> (--count)) & 1);
}

void print_test(unsigned int x, int p, int n, unsigned int y) {
        printf("setbits(0b");
        print_bits(x, 16);
        printf(", %2d, %2d, 0b", p, n);
        print_bits(y, 16);
        printf(") = 0b");
        print_bits(setbits(x, p, n, y), 16);
        putchar('\n');
}
