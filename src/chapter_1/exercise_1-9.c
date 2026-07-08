#include <stdio.h>

int main() {
        int c, is_space = 0;
        while ((c = getchar()) != EOF)
                if (c == ' ') is_space = 1;
                else if (is_space) {
                        putchar(' ');
                        putchar(c);
                        is_space = 0;
                } else putchar(c);
        return 0;
}
