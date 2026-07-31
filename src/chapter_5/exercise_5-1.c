#include <stdio.h>
#include <ctype.h>

int getint(int* result);
int getch(void);
void ungetch(int c);

int main() {
        for (int result; getint(&result) > 0;) printf("%d\n", result);
        return 0;
}

int getint(int* result) {
        int c, sign;
        for (; isspace(c = getch()) ;);
        if (!isdigit(c) && c != '+' && c != '-' && c != EOF) {
                ungetch(c);
                return 0;
        }
        sign = (c == '-') ? -1 : 1;
        int last_c;
        if (c == '+' || c == '-') {
                last_c = c;
                c = getch();
        }
        if (!isdigit(c)) {
                ungetch(last_c);
                ungetch(c);
                return 0;
        }
        for (*result = 0; isdigit(c); c = getch()) *result = 10 * *result + (c - '0');
        *result *= sign;
        if (c != EOF) ungetch(c);
        return c;
}

#define UNGETCH_BUFFER_MAX_LENGTH 100

char ungetch_buffer[UNGETCH_BUFFER_MAX_LENGTH];
int ungetch_buffer_length = 0;

int getch(void) {
        return (ungetch_buffer_length > 0) ?
                ungetch_buffer[--ungetch_buffer_length] :
                getchar();
}

void ungetch(int c) {
        if (ungetch_buffer_length < UNGETCH_BUFFER_MAX_LENGTH)
                ungetch_buffer[ungetch_buffer_length++] = c;
        else printf("error: ungetch buffer limit reached.\n");
}
