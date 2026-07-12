#include <stdio.h>

#define COLUMN_LIMIT 60

int main() {
        int current_column = 0;
        for (int c; (c = getchar()) != EOF; ) {
                if (c == '\n') current_column = 0;
                else ++current_column;
                if (
                        current_column >= COLUMN_LIMIT &&
                        c != ' ' &&
                        c != '\t' &&
                        c != '\n'
                ) {
                        if (current_column == COLUMN_LIMIT) printf("-\n");
                        else if (current_column > COLUMN_LIMIT) putchar('\n');
                        current_column = 1;
                }
                putchar(c);
        }
        return 0;
}
