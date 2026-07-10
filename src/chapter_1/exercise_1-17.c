#include <stdio.h>

#define MAX_LINE_LENGTH 1000
#define COLUMN_LIMIT 80

int my_getline(char s[], int max_length);

int main() {
        char line[MAX_LINE_LENGTH];
        int line_length;
        while ((line_length = my_getline(line, MAX_LINE_LENGTH)) > 0) {
                if (line_length > COLUMN_LIMIT) {
                        printf("%s", line);
                        if (line_length > MAX_LINE_LENGTH) {
                                printf(
                                        "(...+%d letters)\n",
                                        line_length - MAX_LINE_LENGTH + 1
                                );
                        }
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
