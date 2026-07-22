#include <stdio.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

void reverse(char s[]);
void itob(int n, char s[], int b);

int main() {
        char s[1000];
        itob(27430, s, 16);
        printf("%s\n", s);

        itob(-973, s, 32);
        printf("%s\n", s);

        itob(7354004, s, 2);
        printf("%s\n", s);

        itob(7354004, s, 3);
        printf("%s\n", s);

        itob(-23470, s, 36);
        printf("%s\n", s);
        return 0;
}

void reverse(char s[]) {
        int n = strlen(s);
        char c;
        for (int i = 0; i < n / 2; i++) {
                c = s[i];
                s[i] = s[n - i - 1];
                s[n - i - 1] = c;
        }
}

// supports b up to 36
void itob(int n, char s[], int b) {
        char base[] = "0123456789abcdefghijklmnopqrstuvwxyz";
        int r, i = 0, is_positive = (n > 0) ? TRUE : FALSE;
        // TODO: fix for n = INT_MIN
        if (n < 0) n = -n;
        for (;n; n /= b) {
                r = n % b;
                s[i++] = base[r];
        }
        if (!is_positive) s[i++] = '-';
        s[i] = '\0';
        reverse(s);
}
