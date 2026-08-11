#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct keyword {
        const char *name;
        int count;
};

struct keyword keytab[] = {
        {"auto", 0},
        {"break", 0},
        {"case", 0},
        {"char", 0},
        {"const", 0},
        {"continue", 0},
        {"default", 0},
        {"do", 0},
        {"double", 0},
        {"else", 0},
        {"enum", 0},
        {"extern", 0},
        {"float", 0},
        {"for", 0},
        {"goto", 0},
        {"if", 0},
        {"int", 0},
        {"long", 0},
        {"register", 0},
        {"return", 0},
        {"short", 0},
        {"signed", 0},
        {"sizeof", 0},
        {"static", 0},
        {"struct", 0},
        {"swtich", 0},
        {"typedef", 0},
        {"union", 0},
        {"unsigned", 0},
        {"void", 0},
        {"volatile", 0},
        {"while", 0},
};

#define TRUE 1
#define FALSE 0
#define MAX_WORD_LENGTH 100
#define NKEYS (sizeof(keytab) / sizeof(keytab[0]))

int getword(char *s, int max_len);
int binsearch(char *s, struct keyword *keys, int length);

int main() {
        char s[MAX_WORD_LENGTH];
        int i, in_string = FALSE, in_single_line_comment = FALSE,
                in_multiline_comment = FALSE;
        for (; getword(s, MAX_WORD_LENGTH) != EOF; ) {
                if (
                        strcmp(s, "\"") == 0 &&
                        !in_single_line_comment &&
                        !in_multiline_comment
                ) in_string = !in_string;
                if (in_string) continue;
                if (in_single_line_comment || in_multiline_comment) {
                        if (
                                (in_single_line_comment && strcmp(s, "\n") != 0) ||
                                (in_multiline_comment && strcmp(s, "*/") != 0)
                        ) continue;
                        in_single_line_comment = FALSE;
                        in_multiline_comment = FALSE;
                } else if (strcmp(s, "//") == 0) in_single_line_comment = TRUE;
                else if (strcmp(s, "/*") == 0) in_multiline_comment = TRUE;
                if (isalpha(s[0]) && (i = binsearch(s, keytab, NKEYS)) >= 0)
                        keytab[i].count++;
        }
        for (i = 0; i < NKEYS; i++) if (keytab[i].count > 0)
                printf("%5d %s\n", keytab[i].count, keytab[i].name);
        return 0;
}

#define UNGETCH_BUFFER_CAPACITY 100

char ungetch_buffer[UNGETCH_BUFFER_CAPACITY];
char *ungetch_buffer_p = ungetch_buffer;

int getch(void) {
        return (ungetch_buffer_p > ungetch_buffer) ? *--ungetch_buffer_p : getchar();
}

void ungetch(char c) {
        if (ungetch_buffer + UNGETCH_BUFFER_CAPACITY - ungetch_buffer_p > 0)
                *ungetch_buffer_p++ = c;
        else printf("error: ungetch buffer limit reached.\n");
}

int getword(char *s, int max_len) {
        int c;
        char *w = s;
        for (; (c = getch()) == ' ' || c == '\t'; );
        if (c != EOF && max_len--) *w++ = c;
        if (c == '\\') {
                c = getch();
                if (!isspace(c) && max_len--) {
                        *w++ = c;
                        *w = '\0';
                        return s[0];
                }
                ungetch(c);
        } else if (c == '/' || c == '*') {
                c = getch();
                if (
                        (
                                (*(w - 1) == '/' && c == '/') ||
                                (*(w - 1) == '/' && c == '*') ||
                                (*(w - 1) == '*' && c == '/')
                        ) &&
                        max_len--
                ) {
                        *w++ = c;
                        *w = '\0';
                        return s[0];
                }
                ungetch(c);
        } else if (!isalpha(c) && c != '_' && c != '#') {
                *w = '\0';
                return c;
        }
        for (; max_len-- && isalnum(c = getch()); ) *w++ = c;
        if (!isalnum(c)) ungetch(c);
        *w = '\0';
        return s[0];
}

int binsearch(char *s, struct keyword *keys, int length) {
        int m, l = 0, r = length - 1, compare;
        while (l <= r) {
                m = (l + r) / 2;
                if ((compare = strcmp(s, keys[m].name)) < 0) r = m - 1;
                else if (compare > 0) l = m + 1;
                else return m;
        }
        return -1;
}
