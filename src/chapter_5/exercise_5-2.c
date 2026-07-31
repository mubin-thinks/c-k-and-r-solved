#include <stdio.h>
#include <ctype.h>

// The floatint-point analog of getint will also return
// `int` as the return type as it indicates what characters
// are read and not the number read.
int getfloat(float* result);
int getch(void);
void ungetch(int c);

int main() {
        for (float result; getfloat(&result) > 0;) printf("%f\n", result);
        return 0;
}

int getfloat(float* result) {
        int c, sign;
        for (; isspace(c = getch()); );
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
        for (*result = 0.0; isdigit(c); c = getch())
                *result = 10.0 * *result + (float)(c - '0');
        *result *= sign;
        if (c == '.') c = getch();
        float power = 1.0;
        for (; isdigit(c); c = getch()) {
                *result = 10.0 * *result + (float)(c - '0');
                power *= 10.0;
        }
        *result /= power;
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
