#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
        int n = 4, m = 0;
        for (; --argc && ++argv; ) {
                if (strncmp(*argv, "-", 1) == 0) m = atoi((*argv) + 1);
                else if (strncmp(*argv, "+", 1) == 0) n = atoi((*argv) + 1);
                else {
                        printf("error: invalid command `%s`.\n", *argv);
                        return 1;
                }
        }
        for (int c, col = 0; (c = getchar()) != EOF; ) {
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
                if (c == '\t') for (int i = 0; i < n; i++) putchar(' ');
                else putchar(c);
                col++;
        }
        return 0;
}
