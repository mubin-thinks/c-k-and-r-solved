#include <stdio.h>
#include <string.h>

void reverse(char s[]);

int main() {
        char s[1000];
        strcpy(s, "this is some message");
        reverse(s);
        printf("%s\n", s);
        return 0;
}

void reverse(char s[]) {
        static int l = 0, r = 0, tmp;
        if (s[r + 1] != '\0') {
                r++;
                reverse(s);
        }
        if (l + 1 > r - 1) return;
        tmp = s[l];
        s[l] = s[r];
        s[r] = tmp;
        l++;
        r--;
}
