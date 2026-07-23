#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_OP_LENGTH 100
#define NUMBER '0'

char getop(char s[]);
void push(double x);
double pop(void);

int main() {
        char c, s[MAX_OP_LENGTH];
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

char getop(char s[]) {
        char c;
        for (; (c = getc(stdin)) == ' ' || c == '\t'; );
        if (!isdigit(c) && c != '.') return c;
        int i = 0;
        s[i++] = c;
        for (; isdigit(c = getc(stdin)); ) s[i++] = c;
        if (c == '.') {
                s[i++] = c;
                for (; isdigit(c = getc(stdin)); ) s[i++] = c;
        }
        s[i] = '\0';
        if (c != EOF) ungetc(c, stdin);
        return NUMBER;
}

#define STACK_SIZE 100

double stack[STACK_SIZE];
int stack_idx = 0;

void push(double x) {
        if (stack_idx < STACK_SIZE) stack[stack_idx++] = x;
        else printf("error: stack limit reached.\n");
}

double pop(void) {
        if (stack_idx >= 0) return stack[--stack_idx];
        else {
                printf("error: empty stack.\n");
                return 0.0;
        }
}
