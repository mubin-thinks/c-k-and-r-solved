#include <stdio.h>

#define SPACES_FOR_A_TAB 8

int main() {
        int space_count = 0;
        for (int c; (c = getchar()) != EOF; ) {
                if (c == ' ') ++space_count;
                if (space_count >= SPACES_FOR_A_TAB) {
                        space_count -= SPACES_FOR_A_TAB;
                        putchar('\t');
                }
                if (c != ' ') {
                        for (int i = 0; i < space_count; ++i) putchar(' ');
                        space_count = 0;
                        putchar(c);
                }
        }
        return 0;
}
