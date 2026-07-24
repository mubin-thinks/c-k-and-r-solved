#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define OP_MAX_LENGTH 100
#define STACK_MAX_LENGTH 100
double stack[STACK_MAX_LENGTH];
int stack_length = 0;

int is_number(char str[]);
char getch(void);
void ungetch(char c);
int get_token(char s[]);
void stack_push(double x);
double stack_pop(void);
int stack_is_empty(void);
double stack_top(void);
void stack_swap_top(void);
void stack_clear(void);

int main() {
        char c, s[OP_MAX_LENGTH];
        double last_operand, last_top = -1e70;
        int s_length;
        for (; (s_length = get_token(s)) > 0; ) {
                if (is_number(s)) stack_push(atof(s));
                else if (strcmp(s, "+") == 0) stack_push(stack_pop() + stack_pop());
                else if (strcmp(s, "*") == 0) stack_push(stack_pop() * stack_pop());
                else if (strcmp(s, "-") == 0) {
                        last_operand = stack_pop();
                        stack_push(stack_pop() - last_operand);
                } else if (strcmp(s, "/") == 0) {
                        last_operand = stack_pop();
                        stack_push(stack_pop() / last_operand);
                } else if (strcmp(s, "%") == 0) {
                        last_operand = stack_pop();
                        stack_push((int)stack_pop() % (int)last_operand);
                } else if (strcmp(s, "t") == 0) printf("        %.8g\n", stack_top());
                else if (strcmp(s, "d") == 0) stack_push(stack_top());
                else if (strcmp(s, "s") == 0) stack_swap_top();
                else if (strcmp(s, "c") == 0) stack_clear();
                else if (strcmp(s, "sin") == 0) stack_push(sin(stack_pop()));
                else if (strcmp(s, "cos") == 0) stack_push(cos(stack_pop()));
                else if (strcmp(s, "tan") == 0) stack_push(tan(stack_pop()));
                else if (strcmp(s, "asin") == 0) stack_push(asin(stack_pop()));
                else if (strcmp(s, "acos") == 0) stack_push(acos(stack_pop()));
                else if (strcmp(s, "atan") == 0) stack_push(atan(stack_pop()));
                else if (strcmp(s, "exp_e") == 0) stack_push(exp(stack_pop()));
                else if (strcmp(s, "ln") == 0) stack_push(log(stack_pop()));
                else if (strcmp(s, "log_10") == 0) stack_push(log10(stack_pop()));
                else if (strcmp(s, "pow") == 0) {
                        last_operand = stack_pop();
                        stack_push(pow(stack_pop(), last_operand));
                } else if (strcmp(s, "sqrt") == 0) stack_push(sqrt(stack_pop()));
                else if (strcmp(s, "view_stack") == 0) {
                        printf("[");
                        for (int i = 0; i < stack_length; i++) {
                                if (i < stack_length - 1 && i % 10 == 0)
                                        printf("\n        ");
                                printf("%.3g, ", stack[i]);
                        }
                        printf("\n]\n");
                } else if (strcmp(s, "\n") == 0) {
                        if (
                                !stack_is_empty() &&
                                (last_operand = stack_pop()) != last_top
                        ) {
                                printf("        %.8g\n", last_operand);
                                last_top = last_operand;
                        }
                } else printf("error: unkown command/function '%s'\n", s);
        }
        return 0;
}

int is_number(char str[]) {
        for (int i = 0; str[i] != '\0'; i++) {
                if (!isdigit(str[i]) && str[i] != '.' && str[i] != 'e' && str[i] != 'E')
                        return 0;
        }
        return 1;
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

int get_token(char s[]) {
        char c;
        for (; (c = getch()) == ' ' || c == '\t'; );
        int i = 0;
        s[i++] = c;
        if (c == '\n') {
                s[i] = '\0';
                return i;
        }
        for (; (c = getchar()) != EOF && !isspace(c); ) s[i++] = c;
        if (c != EOF) ungetch(c);
        s[i] = '\0';
        return i;
}

void stack_push(double x) {
        if (stack_length < STACK_MAX_LENGTH) stack[stack_length++] = x;
        else printf("error: stack limit reached.\n");
}

double stack_pop(void) {
        if (stack_length > 0) return stack[--stack_length];
        else {
                printf("error: empty stack.\n");
                return 0.0;
        }
}

int stack_is_empty(void) {
        return (stack_length > 0) ? 0 : 1;
}

double stack_top(void) {
        if (stack_length > 0) return stack[stack_length - 1];
        else {
                printf("error: empty stack.\n");
                return 0.0;
        }
}

void stack_swap_top(void) {
        if (stack_length >= 2) {
                double tmp = stack[stack_length - 1];
                stack[stack_length - 1] = stack[stack_length - 2];
                stack[stack_length - 2] = tmp;
        }
}

void stack_clear(void) {
        stack_length = 0;
}
