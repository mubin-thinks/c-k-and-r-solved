#include <stdio.h>

#define MAX_LINE_LENGTH 1000

int main() {
        int c, i = 0;
        char s[MAX_LINE_LENGTH];
        for (; (i < MAX_LINE_LENGTH - 1) * ((c = getchar()) != '\n') * (c != EOF); ++i)
                s[i] = c;
        s[i] = '\0';
        printf("%s\n", s);
        return 0;
}
