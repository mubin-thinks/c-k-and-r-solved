#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define COLUMN_LIMIT 60
#define WORD_CAPACITY 200

enum print_style_e {
        OCTAL,
        HEXADECIMAL,
};

enum {
        OK,
        ERROR,
};

int parse_arguments(char *p, enum print_style_e *non_graphic_print_style);
int is_ascii(int c);
int read_word(char *s, int s_len, enum print_style_e non_graphic_print_style);

int main(int argc, char **argv) {
        enum print_style_e non_graphic_print_style = HEXADECIMAL;
        if (argc > 1 && parse_arguments(*(argv + 1), &non_graphic_print_style) != OK) {
                printf("error: expected -o or -x\n");
                return 1;
        }
        char s[WORD_CAPACITY];
        int s_len, current_col = 0;
        for (; (s_len = read_word(s, WORD_CAPACITY, non_graphic_print_style)) > 0; ) {
                if (s_len > COLUMN_LIMIT) {
                        if (current_col > 0) {
                                putchar(' ');
                                current_col++;
                        }
                        for (char *p = s; *p; p++) {
                                if (current_col >= COLUMN_LIMIT - 1) {
                                        printf("-\n");
                                        current_col = 0;
                                }
                                putchar(*p);
                                current_col++;
                        }
                } else {
                        if (current_col + s_len + (current_col > 0) <= COLUMN_LIMIT) {
                                if (current_col > 0) {
                                        putchar(' ');
                                        current_col++;
                                }
                                current_col += printf("%s", s);
                        } else {
                                putchar('\n');
                                current_col = printf("%s", s);
                        }
                }
        }
        putchar('\n');
        return 0;
}

int parse_arguments(char *p, enum print_style_e *non_graphic_print_style) {
        if (*(p++) != '-') return ERROR;
        if (*p == 'o') *non_graphic_print_style = OCTAL;
        else if (*p == 'x') *non_graphic_print_style = HEXADECIMAL;
        if (*p == 'o' || *p == 'x') return OK;
        return ERROR;
}

int is_ascii(int c) {
        return c <= 127;
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

void skip_blanks() {
        int c;
        for (; (c = getch()) != EOF && isspace(c); );
        ungetch(c);
}

int read_word(char *s, int s_len, enum print_style_e non_graphic_print_style) {
        skip_blanks();
        int c;
        char *p = s;
        char format[4];
        strcpy(format, (non_graphic_print_style == OCTAL) ? "\\%o" : "\\%x");
        for (; (c = getch()) != EOF && !isspace(c); ) {
                if (!is_ascii(c)) p += sprintf(p, format, c);
                else *p++ = c;
        }
        if (c != EOF) ungetch(c);
        *p = '\0';
        return p - s;
}
