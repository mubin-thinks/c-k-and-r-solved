#include <stdio.h>
#include <string.h>

char* my_strncpy(char* s, char* t, int n);
char* my_strncat(char* s, char* t, int n);
int my_strncmp(char* s, char* t, int n);

int main() {
        return 0;
}

char* my_strncpy(char* s, char* t, int n) {
        for (; n-- && *s++ = *t++; );
        if (n > 0) for (; n--; ) *s++ = '\0';
}

char* my_strncat(char* s, char* t, int n) {
        for (; *s != '\0'; s++);
        for (; n-- && *s++ = *t++; );
        if (*(s - 1) != '\0') *s = '\0';
}

int my_strncmp(char* s, char* t, int n) {
        for (; n-- && *s == *t; s++, t++)
                if (*s == '\0') return 0;
        return *s - *t;
}
