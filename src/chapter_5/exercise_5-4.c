#include <stdio.h>

size_t strlen(char* s);
int strend(char* s, char* t);

int main() {
        printf("%d\n", strend("hello", "world"));
        printf("%d\n", strend("hello", "o"));
        printf("%d\n", strend("test", "atest"));
        printf("%d\n", strend("test", "test"));
        printf("%d\n", strend("abcd", ""));
        printf("%d\n", strend("", "world"));
        printf("%d\n", strend("", ""));
        return 0;
}

size_t strlen(char* s) {
        char *p = s;
        for (; *s != '\0'; s++);
        return s - p;
}

int strend(char* s, char* t) {
        for (; *s != '\0'; s++);
        s -= strlen(t);
        for (; *s == *t; s++, t++)
                if (*s == '\0') return 1;
        return 0;
}
