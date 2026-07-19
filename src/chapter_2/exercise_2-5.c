#include <stdio.h>

int is_char_in_string(const char s[], char c);
int any(const char s1[], const char s2[]);

int main() {
        printf("%d\n", any("hello", "lo"));
        printf("%d\n", any("something-abc", "something-"));
        printf("%d\n", any("", "abdef"));
        printf("%d\n", any("this is some text as example.", "abc"));
        printf("%d\n", any("unchanged text", ""));
        return 0;
}

int is_char_in_string(const char s[], char c) {
        for (int i = 0; s[i] != '\0'; ++i)
                if (s[i] == c) return 1;
        return 0;
}

int any(const char s1[], const char s2[]) {
        for (int i = 0; s1[i] != '\0'; ++i)
                if (is_char_in_string(s2, s1[i])) return i;
        return -1;
}
