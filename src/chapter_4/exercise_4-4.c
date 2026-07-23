#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define OP_MAX_LENGTH 100
#define NUMBER '0'

char getch(void);
void ungetch(char c);
char getop(char s[]);
void push(double x);
double pop(void);
double view_top(void);
void swap_top(void);
void clear(void);

int main() {
        char c, s[OP_MAX_LENGTH];
        double last_operand;
        for (; (c = getop(s)) != EOF; ) {
                switch (c) {
                case NUMBER:
                        push(atof(s));
                        break;
                case '+':
                        push(pop() + pop());
                        break;
                case '*':
                        push(pop() * pop());
                        break;
                case '-':
                        last_operand = pop();
                        push(pop() - last_operand);
                        break;
                case '/':
                        if ((last_operand = pop()) != 0.0) push(pop() / last_operand);
                        else printf("error: divisor is 0.\n");
                        break;
                case '%':
                        if ((last_operand = pop()) != 0.0)
                                push((int)pop() % (int)last_operand);
                        else printf("error: divisor is 0.\n");
                        break;
                case 't':
                        printf("        %.8g\n", view_top());
                        break;
                case 'd':
                        push(view_top());
                        break;
                case 's':
                        swap_top();
                        break;
                case 'c':
                        clear();
                        break;
                case '\n':
                        printf("        %.8g\n", pop());
                        break;
                default:
                        printf("error: unknown operator/function '%c'.\n", c);
                        break;
                }
        }
        return 0;
}

#define UNGETCH_BUFFER_MAX_LENGTH 100

char ungetch_buffer[UNGETCH_BUFFER_MAX_LENGTH];
int ungetch_buffer_length = 0;

char getch(void) {
        return (ungetch_buffer_length > 0) ?
                ungetch_buffer[--ungetch_buffer_length] :
                getchar();
}

void ungetch(char c) {
        if (ungetch_buffer_length < UNGETCH_BUFFER_MAX_LENGTH)
                ungetch_buffer[ungetch_buffer_length++] = c;
        else printf("error: ungetch buffer limit reached.\n");
}

char getop(char s[]) {
        char c, next_c;
        for (; (c = getch()) == ' ' || c == '\t'; );
        if (!isdigit(c) && c != '.' && c != '-') return c;
        if (c == '-') {
                next_c = getch();
                if (next_c != EOF) ungetch(next_c);
                if (!isdigit(next_c) && next_c != '.') return c;
        }
        int i = 0;
        s[i++] = c;
        if ((c = getch()) == '.') s[i++] = c;
        else if (c != EOF) ungetch(c);
        for (; isdigit(c = getch()); ) s[i++] = c;
        if (c == '.') {
                s[i++] = c;
                for (; isdigit(c = getch()); ) s[i++] = c;
        }
        s[i] = '\0';
        if (c != EOF) ungetch(c);
        return NUMBER;
}

#define STACK_MAX_LENGTH 100

double stack[STACK_MAX_LENGTH];
int stack_length = 0;

void push(double x) {
        if (stack_length < STACK_MAX_LENGTH) stack[stack_length++] = x;
        else printf("error: stack limit reached.\n");
}

double pop(void) {
        if (stack_length > 0) return stack[--stack_length];
        else {
                printf("error: empty stack.\n");
                return 0.0;
        }
}

double view_top(void) {
        if (stack_length > 0) return stack[stack_length - 1];
        else {
                printf("error: empty stack.\n");
                return 0.0;
        }
}

void swap_top(void) {
        if (stack_length >= 2) {
                double tmp = stack[stack_length - 1];
                stack[stack_length - 1] = stack[stack_length - 2];
                stack[stack_length - 2] = tmp;
        }
}

void clear(void) {
        stack_length = 0;
}
