#include <stdio.h>

#define MAX_LINE_LENGTH 1000

int my_getline(char s[], int max_length);

int main() {
        char line[MAX_LINE_LENGTH];
        int line_length;
        while ((line_length = my_getline(line, MAX_LINE_LENGTH)) > 0) {
                int j = line_length - 1;
                for (; j >= 0; --j)
                        if (line[j] != '\t' && line[j] != ' ' && line[j] != '\n') break;
                for (int i = 0; i <= j; ++i) putchar(line[i]);
                if (line_length > 1) putchar('\n');
        }
        return 0;
}

int my_getline(char s[], int max_length) {
        int c, length = 0;
        for (; length < max_length - 2 && (c = getchar()) != EOF && c != '\n'; ++length)
                s[length] = c;
        if (c == '\n') {
                s[length] = '\n';
                ++length;
        }
        s[length] = '\0';
        return length;
}
