#include <stdio.h>

#define MAX_LINE_LENGTH 1000

int my_getline(char s[], int max_length);
void copy(char to[], char from[]);

int main() {
        char line[MAX_LINE_LENGTH], largest_line[MAX_LINE_LENGTH];
        int line_length, largest_line_length = 0;
        while ((line_length = my_getline(line, MAX_LINE_LENGTH)) > 0) {
                if (line_length > largest_line_length) {
                        largest_line_length = line_length;
                        copy(largest_line, line);
                }
        }
        if (largest_line_length > 0) {
                printf("%s", largest_line);
                if (largest_line_length > MAX_LINE_LENGTH) {
                        printf(
                                "(...+%d letters)\n",
                                largest_line_length - MAX_LINE_LENGTH + 1
                        );
                }
        }
        return 0;
}

int my_getline(char s[], int max_length) {
        int c, length = 0;
        for (; length < max_length - 2 && (c = getchar()) != EOF && c != '\n'; ++length)
                s[length] = c;
        if (c == '\n') {
                s[length] = c;
                ++length;
        }
        s[length] = '\0';
        while (c != EOF && c != '\n') {
                ++length;
                c = getchar();
        }
        return length;
}

void copy(char to[], char from[]) {
        for (int i = 0; (to[i] = from[i]) != '\0'; ++i);
}
