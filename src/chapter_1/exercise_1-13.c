#include <stdio.h>

#define IN 0
#define OUT 1

int main() {
        int c, count = 0, state = OUT;
        while ((c = getchar()) != EOF) {
                if (c == ' ' || c == '\t' || c == '\n') {
                        if (state == IN) {
                                for (int i = 0; i < count; i++) putchar('+');
                                putchar('\n');
                                count = 0;
                                state = OUT;
                        }
                } else {
                        count++;
                        state = IN;
                }
        }
        return 0;
}
