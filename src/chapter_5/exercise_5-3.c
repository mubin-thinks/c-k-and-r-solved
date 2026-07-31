#include <stdio.h>

char* strcpy(char* s, char* t);
char* strcat(char* s, char* t);

int main() {
        char s[1000];
        strcpy(s, "something");
        printf("%s\n", strcat(s, " new"));

        strcpy(s, "a");
        printf("%s\n", strcat(s, "bcd"));

        strcpy(s, "hello,");
        printf("%s\n", strcat(s, " world!"));

        strcpy(s, "");
        printf("%s\n", strcat(s, "testing"));

        strcpy(s, "another test");
        printf("%s\n", strcat(s, ""));

        strcpy(s, "");
        printf("%s\n", strcat(s, ""));

        strcpy(s, "a");
        printf("%s\n", strcat(s, "    b    c\0    d"));
        return 0;
}

char* strcpy(char* s, char* t) {
        char* result = s;
        for (; *s++ = *t++; );
        return result;
}

char* strcat(char* s, char* t) {
        char* result = s;
        for (; *s != '\0'; s++);
        for (; *s++ = *t++; );
        return result;
}
