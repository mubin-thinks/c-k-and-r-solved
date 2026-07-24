#include <stdio.h>
#include <ctype.h>

#define NUMBER '0'
#define OP_MAX_LENGTH 100

char getop(char s[]);

int main() {
        char c, s[OP_MAX_LENGTH];
        for (; (c = getop(s)) != EOF; ) printf("%c '%s'\n", c, s);
        return 0;
}

char getop(char s[]) {
        int i = 0;
        static int old_c = -1;
        if (old_c >= 0 && old_c != ' ' && old_c != '\t') {
                int tmp = old_c;
                old_c = -1;
                return tmp;
        }
        char c, next_c;
        for (; (c = getchar()) == ' ' || c == '\t'; );
        if (!isdigit(c) && c != '.') return c;
        s[i++] = c;
        if (isdigit(c)) for (; isdigit(c = getchar()); ) s[i++] = c;
        if (c == '.') for (; isdigit(c = getchar()); ) s[i++] = c;
        s[i] = '\0';
        if (c != EOF) old_c = c;
        return NUMBER;
}
