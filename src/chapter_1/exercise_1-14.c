#include <stdio.h>

#define ASCII_SET_LENGTH 128

int main() {
        int c;
        char char_set[ASCII_SET_LENGTH];
        for (int i = 0; i < ASCII_SET_LENGTH; ++i) char_set[i] = 0;
        while ((c = getchar()) != EOF) ++char_set[c];
        for (int i = 0; i < ASCII_SET_LENGTH; ++i) {
                if (char_set[i] > 0) {
                        if (i == '\n') printf("\\n");
                        else if (i == '\t') printf("\\t");
                        else {
                                putchar(i);
                                putchar(' ');
                        }
                        printf("(%5d) ", char_set[i]);
                        for (int j = 0; j < char_set[i]; ++j) putchar('+');
                        putchar('\n');
                }
        }
        return 0;
}
