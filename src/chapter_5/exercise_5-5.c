#include <stdio.h>

char* strncpy(char* s, char* t, int n);
char* strncat(char* s, char* t, int n);
int strncmp(char* s, char* t, int n);

int main() {
        char s[1000];
        printf("%s\n", strncpy(s, "example", 8));

        strncpy(s, "this text needs to be null-terminated.", 4);
        s[4] = '\0';
        printf("%s\n", s);

        printf("%s\n", strncpy(s, "a", 2));
        printf("%s\n", strncpy(s, "", 1000));
        printf("%s\n", strncpy(s, "test", 0));

        strncat(s, "hello world!", 5);
        strncat(s, " some other text.", 11);
        strncat(s, " abcdefgh", 6);
        strncat(s, " done.", 6);
        strncat(s, "", 1000);
        printf("%s\n", s);

        printf("%d\n", strncmp(s, "hello", 5));
        printf("%d\n", strncmp(s + 5, " some other", 11));
        printf("%d\n", strncmp(s + 5, " some other", 5));
        printf("%d\n", strncmp(s + 23, "done.", 5));
        printf("%d\n", strncmp(s, "will not match", 5));
        return 0;
}

char* strncpy(char* s, char* t, int n) {
        char *p = s;
        for (; n-- && (*p++ = *t++); );
        if (n > 0) for (; n--; ) *p++ = '\0';
        return s;
}

char* strncat(char* s, char* t, int n) {
        char *p = s;
        for (; *p != '\0'; p++);
        for (; n-- && (*p++ = *t++); );
        if (*(p - 1) != '\0') *p = '\0';
        return s;
}

int strncmp(char* s, char* t, int n) {
        for (; n-- && (*s == *t); s++, t++) if (*s == '\0' || n == 0) return 0;
        return *s - *t;
}
