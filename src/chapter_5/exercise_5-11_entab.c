#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
        int space_count_for_tab = 4;
        if (argc >= 2) {
                space_count_for_tab = atoi(argv[1]);
                if (!space_count_for_tab) {
                        printf("error: provide positive integer.\n");
                        return 1;
                }
        }
        int space_count = 0;
        for (int c; (c = getchar()) != EOF; ) {
                if (c == ' ') space_count++;
                else {
                        for (int i = 0; i < space_count; i++) putchar(' ');
                        space_count = 0;
                        putchar(c);
                }
                if (space_count >= space_count_for_tab) {
                        putchar('\t');
                        space_count -= space_count_for_tab;
                }
        }
        return 0;
}
