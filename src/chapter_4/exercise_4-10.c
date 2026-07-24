#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define OP_MAX_LENGTH 100
#define LINE_MAX_LENGTH 1000
#define STACK_MAX_LENGTH 100
double stack[STACK_MAX_LENGTH];
int stack_length = 0;

int is_number(char str[]);
int get_line(char s[]);
void stack_push(double x);
double stack_pop(void);
int stack_is_empty(void);
double stack_top(void);
void stack_swap_top(void);
void stack_clear(void);

int main() {
        char s[OP_MAX_LENGTH], line[LINE_MAX_LENGTH];
        double last_operand, ans = 0.0, variables[26];
        int s_length = 0, line_length, line_idx = 0;
        for (; (line_length = get_line(line)) > 0; ) {
                for (; line_idx < line_length; ) {
                        for (
                                ;
                                line[line_idx] == ' ' || line[line_idx] == '\t';
                                line_idx++
                        );
                        if (line[line_idx] == '\n') {
                                s[s_length++] = line[line_idx++];
                                s[s_length] = '\0';
                        } else {
                                for (
                                        ;
                                        line[line_idx] != EOF && !isspace(line[line_idx]);
                                        line_idx++
                                ) s[s_length++] = line[line_idx];
                                s[s_length] = '\0';
                        }

                        if (is_number(s)) stack_push(atof(s));
                        else if (strcmp(s, "+") == 0)
                                stack_push(stack_pop() + stack_pop());
                        else if (strcmp(s, "*") == 0)
                                stack_push(stack_pop() * stack_pop());
                        else if (strcmp(s, "-") == 0) {
                                last_operand = stack_pop();
                                stack_push(stack_pop() - last_operand);
                        } else if (strcmp(s, "/") == 0) {
                                last_operand = stack_pop();
                                stack_push(stack_pop() / last_operand);
                        } else if (strcmp(s, "%") == 0) {
                                last_operand = stack_pop();
                                stack_push((int)stack_pop() % (int)last_operand);
                        } else if (strcmp(s, "t") == 0) stack_push(stack_top());
                        else if (strcmp(s, "d") == 0) {
                                stack_push(stack_top());
                                stack_push(stack_top());
                        }
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
                        else if (strcmp(s, "e") == 0) stack_push(exp(1));
                        else if (strcmp(s, "pi") == 0) stack_push(M_PI);
                        else if (strcmp(s, "pow") == 0) {
                                last_operand = stack_pop();
                                stack_push(pow(stack_pop(), last_operand));
                        } else if (strcmp(s, "sqrt") == 0) stack_push(sqrt(stack_pop()));
                        else if (strcmp(s, "view_stack") == 0) {
                                printf("[\n        ");
                                for (int i = 0; i < stack_length; i++) {
                                        printf("%.3g, ", stack[i]);
                                        if ((i + 1) % 10 == 0) printf("\n        ");
                                }
                                printf("\n]\n");
                        } else if (strcmp(s, "\n") == 0) {
                                if (!stack_is_empty()) {
                                        printf(
                                                "        %.8g\n",
                                                (ans = stack_pop())
                                        );
                                }
                        } else if (s_length == 1 && isupper(s[0]))
                                stack_push(variables[s[0] - 'A']);
                        else if (
                                s_length == 5 &&
                                strncmp(s, "set_", 4) == 0 && isupper(s[4])
                        ) {
                                if (stack_length > 0) variables[s[4] - 'A'] = stack_top();
                        }
                        else if (strcmp(s, "ans") == 0) stack_push(ans);
                        else printf("error: unkown command/function '%s'\n", s);
                        s_length = 0;
                }
                line_idx = 0;
        }
        return 0;
}

int is_number(char str[]) {
        for (int i = 0; str[i] != '\0'; i++)
                if (!isdigit(str[i]) && str[i] != '.') return 0;
        return 1;
}

int get_line(char s[]) {
        int i = 0, c;
        for (; (c = getchar()) != EOF && c != '\n'; i++) s[i] = c;
        if (c == '\n') s[i++] = '\n';
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
