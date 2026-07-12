#include <stdio.h>

#define IN 0
#define OUT 1
#define MAX_WORD_COUNT 10000

int main() {
        int c, state = OUT, word_lengths_idx = 0, count = 0;
        int word_lengths[MAX_WORD_COUNT];
        while ((c = getchar()) != EOF) {
                if (c == ' ' || c == '\t' || c == '\n') {
                        if (state == IN) {
                                word_lengths[word_lengths_idx] = count;
                                ++word_lengths_idx;
                                count = 0;
                                state = OUT;
                        }
                }
                else {
                        ++count;
                        state = IN;
                }
        }

        int max_length = 0;
        for (int i = 0; i < word_lengths_idx; ++i)
                if (word_lengths[i] > max_length) max_length = word_lengths[i];

        for (int i = max_length; i >= 1; i--) {
                for (int j = 0; j < word_lengths_idx; ++j) {
                        if (word_lengths[j] >= i) putchar('+');
                        else putchar(' ');
                }
                putchar('\n');
        }
        return 0;
}
