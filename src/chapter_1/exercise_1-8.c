#include <stdio.h>

int main() {
        int c, blank_count, tab_count, newline_count;
        blank_count = tab_count = newline_count = 0;

        while ((c = getchar()) != EOF) {
                if (c == ' ') ++blank_count;
                else if (c == '\t') ++tab_count;
                else if (c == '\n') ++newline_count;
        }

        printf(
                "%d blanks\n%d tabs\n%d newlines\n",
                blank_count,
                tab_count,
                newline_count
        );

        return 0;
}
