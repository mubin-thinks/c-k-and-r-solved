#include <stdio.h>

#define COLUMN_LIMIT 60
#define TRUE 1
#define FALSE 0

int main() {
        int current_column = 0, line[COLUMN_LIMIT];
        int track_space = FALSE, space_idx = -1;
        for (int c; (c = getchar()) != EOF; ) {
                if (current_column == COLUMN_LIMIT) {
                        if (space_idx != -1) {
                                for (int i = 0; i < space_idx - 1; ++i) putchar(line[i]);
                                putchar('\n');
                                int j = 0;
                                for (int i = space_idx; i < current_column; ++i, ++j)
                                        line[j] = line[i];
                                current_column = j;
                                space_idx = -1;
                        } else {
                                for (int i = 0; i < current_column - 1; ++i)
                                        putchar(line[i]);
                                printf("-\n");
                                line[0] = line[current_column - 1];
                                current_column = 1;
                        }
                }
                line[current_column] = c;
                ++current_column;
                if (c != ' ' && c != '\t' && c != '\n') track_space = TRUE;
                if (track_space == TRUE && c == ' ') {
                        space_idx = current_column;
                        track_space = FALSE;
                }
                if (c == '\n') {
                        for (int i = 0; i < current_column - 1; ++i) putchar(line[i]);
                        putchar('\n');
                        current_column = 0;
                        space_idx = -1;
                }
        }
        return 0;
}
