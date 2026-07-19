#include <stdio.h>
#include <string.h>

int is_char_in_string(const char s[], char c);
void squeeze(char s1[], const char s2[]);

int main() {
        char s[1000];
        strcpy(s, "hello");
        squeeze(s, "lo");
        printf("%s\n", s);

        strcpy(s, "something-abc");
        squeeze(s, "something-");
        printf("%s\n", s);

        strcpy(s, "");
        squeeze(s, "abdef");
        printf("%s\n", s);

        strcpy(s, "this is some text as example.");
        squeeze(s, "abc");
        printf("%s\n", s);

        strcpy(s, "unchanged text");
        squeeze(s, "");
        printf("%s\n", s);
        return 0;
}

int is_char_in_string(const char s[], char c) {
        for (int i = 0; s[i] != '\0'; ++i)
                if (s[i] == c) return 1;
        return 0;
}

void squeeze(char s1[], const char s2[]) {
        int i = 0, j = 0;
        for (; s1[i] != '\0'; ++i)
                if (!is_char_in_string(s2, s1[i])) s1[j++] = s1[i];
        s1[j] = '\0';
}
