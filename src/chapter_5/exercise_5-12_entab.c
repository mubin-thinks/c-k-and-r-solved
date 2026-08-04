#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
        int n = 4, m = 0;
        for (; --argc && ++argv; ) {
                if (**argv = '-') m = atoi(*argv + 1);
                else if (**argv = '+') n = atoi(*argv + 1);
                else {
                        printf("error: invalid command `%s`.\n", *argv);
                        return 1;
                }
        }
        int space_count = 0, col = 0;
        for (int c; (c = getchar()) != EOF; ) {
                if (c == '\n') {
                        putchar(c);
                        col = 0;
                        continue;
                }
                if (col < m) {
                        putchar(c);
                        col++;
                        continue;
                }
                if (c == ' ') space_count++;
                else {
                        for (int i = 0; i < space_count; i++) putchar(' ');
                        space_count = 0;
                        putchar(c);
                }
                if (space_count >= n) {
                        putchar('\t');
                        space_count -= n;
                }
                col++;
        }
        return 0;
}
