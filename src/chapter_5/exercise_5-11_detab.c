#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
        int spaces_per_tab = 4;
        if (argc >= 2) {
                spaces_per_tab = atoi(argv[1]);
                if (!spaces_per_tab) {
                        printf("error: provide positive integer.\n");
                        return 1;
                }
        }
        for (int c; (c = getchar()) != EOF; ) {
                if (c == '\t') for (int i = 0; i < spaces_per_tab; i++) putchar(' ');
                else putchar(c);
        }
        return 0;
}
