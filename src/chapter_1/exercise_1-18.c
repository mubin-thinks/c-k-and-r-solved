#include <stdio.h>

#define MAX_LINE_LENGTH 1000

int my_getline(char s[], int max_length);
void remove_trailing_invisible_symbols(char s[], int length);

int main() {
        char line[MAX_LINE_LENGTH];
        int line_length;
        while ((line_length = my_getline(line, MAX_LINE_LENGTH)) > 0) {
                remove_trailing_invisible_symbols(line, line_length);
                printf("%s", line);
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

void remove_trailing_invisible_symbols(char s[], int length) {
        int i = length - 1;
        if (s[i] == '\n') --i;
        for (; s[i] == ' ' || s[i] == '\t'; --i);
        s[i + 1] = '\0';
}
