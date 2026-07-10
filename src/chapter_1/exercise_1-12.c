#include <stdio.h>

#define IN 0
#define OUT 1

int main() {
        int c, state = OUT;
        while ((c = getchar()) != EOF) {
                if (state == IN && (c == ' ' || c == '\t' || c == '\n')) {
                        putchar('\n');
                        state = OUT;
                } else {
                        putchar(c);
                        state = IN;
                }
        }
        return 0;
}
