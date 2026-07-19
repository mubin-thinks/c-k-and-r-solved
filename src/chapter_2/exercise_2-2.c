#include <stdio.h>

#define MAX_LINE_LENGTH 1000

int main() {
        int i = 0;
        char s[MAX_LINE_LENGTH];
        for (
                int c;
                (i < MAX_LINE_LENGTH - 1) + ((c = getchar()) != '\n') + (c != EOF) == 3;
                ++i
        ) s[i] = c;
        s[i] = '\0';
        printf("%s\n", s);
        return 0;
}
