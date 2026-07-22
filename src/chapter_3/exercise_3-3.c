#include <stdio.h>
#include <string.h>

int write_sequence(char s[], int j, char l, char r);
int is_whitespace(char c);
void expand(char s1[], char s2[]);

int main() {
        char in[] = "expand test: a-z z-a 0-9 9-0 -9-0 (-] A-zz-A !-~";
        char out[10000];
        expand(in, out);
        printf("%s\n", out);
        return 0;
}

int write_sequence(char s[], int j, char l, char r) {
        if (l <= r) for (char i = l; i <= r; i++) s[j++] = i;
        else for (char i = l; i >= r; i--) s[j++] = i;
        return j;
}

int is_whitespace(char c) {
        return c == ' ' || c == '\t' || c == '\n';
}

void expand(char s1[], char s2[]) {
        int n = strlen(s1), j = 0;
        for (int i = 0; s1[i] != '\0'; i++) {
                if (
                        s1[i] == '-' &&
                        i > 0 && i < n &&
                        !is_whitespace(s1[i - 1]) && !is_whitespace(s1[i + 1])
                ) {
                        j = write_sequence(s2, --j, s1[i - 1], s1[i + 1]);
                        i++;
                }
                else s2[j++] = s1[i];
        }
        s2[j] = '\0';
}
