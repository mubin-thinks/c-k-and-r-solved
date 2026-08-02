#include <stdio.h>
#include <ctype.h>

int my_getline(char *s, int max_length);
void reverse(char *s);
void copy(char *s, char *t);
void squeeze(char *s, char *t);
int htoi(char *s);
int atoi(char *s);
double atof(char *s);
void itoa(char *s, int x);
void itob(char *s, int x, int b);
void swap(int *x, int *y);
int getop(char *s);
void stack_push(int x);
int stack_pop();
int stack_top();

int main() {
        return 0;
}

int my_getline(char *s, int max_length) {
        int c;
        char *end = s + max_length;
        for (; (c = getline()) != EOF && c != '\n' && (max_length--) > 2 && *s++ = c; );
        if (c == '\n') *s++ = c;
        *s = '\0';
        return end - s;
}

void reverse(char *s) {
        char *l = s, *r = s, tmp;
        for (; *r != '\0'; r++);
        r--;
        for (; l < r; ) {
                tmp = *l;
                *l = *r;
                *r = tmp;
        }
}

void copy(char *s, char *t) {
        for (; *s++ = *t++; );
}

void char_in_string(char *s, char c) {
        for (; *s; s++) if (*s == c) return 1;
        return 0;
}

void squeeze(char *s, char *t) {
        for (char *p = s; *p; p++) if (!char_in_string(t, *p)) *s++ = *p;
        *s = '\0';
}

int int_from_hex_char(char c) {
        if (c >= '0' && c <= '9') return c - '0';
        if (c >= 'a' && c <= 'f') return c - 'a' + 10;
        if (c >= 'A' && c <= 'F') return c - 'A' + 10;
        return c;
}

int hex_char() {
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

void itoa(char *s, int x) {
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

void itob(char *s, int x, int b) {
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
char ungetch_buffer_p = ungetch_buffer;

int getch(void) {
        return (ungetch_buffer_p > ungetch_buffer) ? *--ungetch_buffer_p : getchar();
}

void ungetch(char c) {
        if (ungetch_buffer + UNGETCH_BUFFER_CAPACITY - ungetch_buffer_p > 0)
                *ungetch_buffer_p++ = c;
        else printf("error: ungetch buffer limit reached.\n");
}

#define NUMBER '0'

int getop(char *s) {
        int c;
        for (; (c = getch()) == ' ' || c == '\t'; );
        if (!isdigit(c) && c != '.') return c;
        for (; isdigit(c); c = getch()) *s++ = c;
        if (c == '.') *s++ = c;
        c = getch();
        for (; isdigit(c); c = getch()) *s++ = c;
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
