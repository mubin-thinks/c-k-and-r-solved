#include <stdio.h>
#include <ctype.h>
#include <limits.h>

#define NUMBER '0'

int my_getline(char *s, int max_length);
char *reverse(char *s);
char *copy(char *s, char *t);
char *squeeze(char *s, char *t);
int htoi(char *s);
int atoi(char *s);
double atof(char *s);
char *itoa(char *s, int x);
char *itob(char *s, int x, int b);
void swap(int *x, int *y);
int getop(char *s);
void stack_push(int x);
int stack_pop();
int stack_top();

int main() {
        char s[1000];
        printf("line_length: %d, line: %s\n", my_getline(s, 1000), s);
        printf("reversed: %s\n", reverse(s));
        char t[1000];
        printf("t: %s\n", copy(t, s));
        printf("squeeze(s, \"abcd\"): %s\n", squeeze(s, "abcd"));
        printf("htoi(\"0xff\"): %d\n", htoi("0xff"));
        printf("atoi(\"-00004237934\"): %d\n", atoi("-00004237934"));
        printf("atof(\"-0.00004f\"): %f\n", atoi("0.00004f"));
        printf("itoa(s, 123456789): %s\n", itoa(s, 123456789));
        printf("itob(s, INT_MAX, 36): %s\n", itob(s, INT_MAX, 36));
        int x = 40, y = -32740234;
        printf("int x = %d, y = %d\n", x, y);
        swap(&x, &y);
        printf("swap(&x, &y): x = %d, y = %d\n", x, y);
        printf("math expresssion > ");
        for (int option; (option = getop(s)) != '\n'; ) {
                switch (option) {
                        case NUMBER:
                                printf("NUMBER %s\n", s);
                                break;
                        default:
                                printf("OP %c\n", option);
                                break;
                }
        }

        stack_push(20);
        stack_push(324);
        stack_push(3274);
        stack_push(2);
        stack_push(16);
        printf("stack_pop(): %d\n", stack_pop());
        printf("stack_pop(): %d\n", stack_pop());
        printf("stack_pop(): %d\n", stack_pop());
        printf("stack_top(): %d\n", stack_top());
        printf("stack_top(): %d\n", stack_top());
        printf("stack_top(): %d\n", stack_top());
        printf("stack_pop(): %d\n", stack_pop());
        printf("stack_pop(): %d\n", stack_pop());
        printf("stack_pop(): %d\n", stack_pop());
        printf("stack_top(): %d\n", stack_top());
        return 0;
}

int my_getline(char *s, int max_length) {
        int c;
        char *p = s;
        for (; (c = getchar()) != EOF && c != '\n' && (max_length--) > 2 && (*p++ = c); );
        if (c == '\n') *p++ = c;
        *p = '\0';
        return p - s;
}

char *reverse(char *s) {
        char *l = s, *r = s, tmp;
        for (; *r != '\0'; r++);
        r--;
        for (; l < r; l++, r--) {
                tmp = *l;
                *l = *r;
                *r = tmp;
        }
        return s;
}

char *copy(char *s, char *t) {
        char *p = s;
        for (; *p++ = *t++; );
        return s;
}

int char_in_string(char *s, char c) {
        for (; *s; s++) if (*s == c) return 1;
        return 0;
}

char *squeeze(char *s, char *t) {
        char *p = s, *result = s;
        for (; *p; p++) if (!char_in_string(t, *p)) *s++ = *p;
        *s = '\0';
        return result;
}

int int_from_hex_char(char c) {
        if (c >= '0' && c <= '9') return c - '0';
        if (c >= 'a' && c <= 'f') return c - 'a' + 10;
        if (c >= 'A' && c <= 'F') return c - 'A' + 10;
        return c;
}

int hex_char(char c) {
        if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'))
                return 1;
        return 0;
}

int htoi(char *s) {
        if (*s == '0' && tolower(*(s + 1)) == 'x') s += 2;
        int result = 0;
        for (; hex_char(*s); s++) result = 16 * result + int_from_hex_char(*s);
        return result;
}

int atoi(char *s) {
        for (; isspace(*s); s++);
        int sign = (*s == '-') ? -1 : 1;
        if (*s == '+' || *s == '-') s++;
        int result = 0;
        for (; isdigit(*s); s++) result = 10 * result + (*s - '0');
        return result * sign;
}

double atof(char *s) {
        for (; isspace(*s); s++);
        int sign = (*s == '-') ? -1 : 1;
        if (*s == '+' || *s == '-') s++;
        double result = 0;
        for (; isdigit(*s); s++) result = 10.0 * result + (*s - '0');
        if (*s != '.') return result * sign;
        double power = 0;
        for (s++; isdigit(*s); s++) {
                result = 10.0 * result + (*s - '0');
                power *= 10.0;
        }
        return (result * sign) / power;
}

char *itoa(char *s, int x) {
        char *p = s;
        int sign = (x < 0) ? -1 : 1, add_one = (x == INT_MIN) ? 1 : 0;
        if (x == INT_MIN) x++;
        if (x < 0) x = -x;
        do *p++ = x % 10 + '0'; while ((x /= 10) > 0);
        if (sign < 0) *p++ = '-';
        *s += add_one;
        *p = '\0';
        reverse(s);
}

char *itob(char *s, int x, int b) {
        char *p = s, *base = "0123456789abcdefghijklmnopqrstuvwxyz",
                sign = (x < 0) ? -1 : 1;
        do *p++ = base[x % b]; while ((x /= b) > 0);
        if (sign < 0) *p++ = '-';
        *p = '\0';
        reverse(s);
}

void swap(int *x, int *y) {
        int tmp;
        tmp = *x;
        *x = *y;
        *y = tmp;
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

int getop(char *s) {
        int c;
        for (; (c = getch()) == ' ' || c == '\t'; );
        if (!isdigit(c) && c != '.') return c;
        for (; isdigit(c); c = getch()) *s++ = c;
        if (c == '.') {
                *s++ = c;
                c = getch();
                for (; isdigit(c); c = getch()) *s++ = c;
        }
        *s = '\0';
        if (c != EOF) ungetch(c);
        return NUMBER;
}

#define STACK_CAPACITY 1000

int stack[STACK_CAPACITY];
int *stack_p = stack;

void stack_push(int x) {
        if (stack + STACK_CAPACITY - stack_p > 0) *stack_p++ = x;
}

int stack_pop() {
        if (stack_p > stack) return *--stack_p;
        else return 0;
}

int stack_top() {
        if (stack_p > stack) return *(stack_p - 1);
        else return 0;
}
