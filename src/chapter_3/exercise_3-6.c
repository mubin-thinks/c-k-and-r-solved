#include <stdio.h>
#include <string.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0

void reverse(char s[], int n);
void itoa(int n, char s[], int w);

int main() {
        char s[1000];
        itoa(INT_MIN, s, 16);
        printf("'%s'\n", s);
        return 0;
}

void reverse(char s[], int n) {
        char c;
        for (int i = 0; i < n / 2; i++) {
                c = s[i];
                s[i] = s[n - i - 1];
                s[n - i - 1] = c;
        }
}

void itoa(int n, char s[], int w) {
        int i = 0, is_positive = (n > 0) ? TRUE : FALSE, add_one = (n == INT_MIN) ? 1 : 0;
        if (n == INT_MIN) n++;
        if (n < 0) n = -n;
        do s[i++] = n % 10 + '0'; while ((n /= 10) > 0);
        if (!is_positive) s[i++] = '-';
        s[0] += add_one;
        for (; i < w;) s[i++] = ' ';
        s[i] = '\0';
        reverse(s, i);
}
