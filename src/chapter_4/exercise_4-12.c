#include <stdio.h>
#include <string.h>

int get_digit_count(int n);
void itoa(char s[], int i, int n);

int main() {
        char s[1000];
        itoa(s, 1234, get_digit_count(1234));
        printf("%s\n", s);
        s[0] = '\0';

        itoa(s, 237949, get_digit_count(237949));
        printf("%s\n", s);
        s[0] = '\0';

        itoa(s, -5763487, get_digit_count(-5763487));
        printf("%s\n", s);
        s[0] = '\0';

        itoa(s, 0, get_digit_count(0));
        printf("%s\n", s);
        s[0] = '\0';

        itoa(s, 3409, get_digit_count(3409));
        printf("%s\n", s);
        s[0] = '\0';
        return 0;
}

int get_digit_count(int n) {
        int length = 1;
        for (; n /= 10; length++);
        return length;
}

void itoa(char s[], int n, int digit_count) {
        if (n < 0) {
                s[0] = '-';
                n = -n;
        } else if (s[0] != '+' && s[0] != '-') s[0] = '+';
        if (n / 10) itoa(s, n / 10, digit_count - 1);
        s[digit_count++] = n % 10 + '0';
        s[digit_count] = '\0';
}
