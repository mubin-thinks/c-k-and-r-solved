#include <stdio.h>
#include <string.h>

int ungetch_char = -1;

int getch(void);
void ungetch(char c);
void ungets(const char s[]);

int main() {
        ungetch('a');
        printf("%c\n", getch());
        ungetch('b');
        printf("%c\n", getch());
        ungetch('c');
        printf("%c\n", getch());
        ungetch('`');
        printf("%c\n", getch());
        ungetch('@');
        ungetch('#');
        printf("%c\n", getch());
}

int getch(void) {
        if (ungetch_char >= 0) {
                int tmp = ungetch_char;
                ungetch_char = -1;
                return tmp;
        } else return getchar();
}

void ungetch(char c) {
        if (ungetch_char < 0) ungetch_char = c;
        else printf("error: ungetch_char is set.\n");
}
