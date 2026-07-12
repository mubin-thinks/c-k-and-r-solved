#include <stdio.h>

#define MAX_LINE_LENGTH 1000

int my_getline(char s[], int max_length);
int length(char s[]);
void reverse(char s[]);

int main() {
        char line[MAX_LINE_LENGTH];
        int line_length;
        while ((line_length = my_getline(line, MAX_LINE_LENGTH)) > 0) {
                reverse(line);
                printf("%s", line);
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
        return length;
}

int length(char s[]) {
        int result = 0;
        for (; s[result] != '\0'; ++result);
        return result;
}

void reverse(char s[]) {
        int n = length(s);
        if (s[n - 1] == '\n') --n;
        char tmp;
        for (int i = 0; i < n / 2; ++i) {
                tmp = s[i];
                s[i] = s[n - i - 1];
                s[n - i - 1] = tmp;
        }
}
