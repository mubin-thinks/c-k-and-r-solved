// Compile command to generate executable `expr`:
//        gcc -o expr exercise_5-10.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_number(char *s);
void stack_push(double x);
double stack_pop();
double stack_top();

int main(int argc, char *argv[]) {
        if (argc < 2) {
                printf("usage: %s <reverse polish math expression>\n", argv[0]);
                return 1;
        }
        for (double last_operand; --argc && ++argv; ) {
                if (is_number(*argv)) stack_push(atof(*argv));
                else if (strcmp(*argv, "+") == 0) stack_push(stack_pop() + stack_pop());
                else if (strcmp(*argv, "*") == 0) stack_push(stack_pop() * stack_pop());
                else if (strcmp(*argv, "-") == 0) {
                        last_operand = stack_pop();
                        stack_push(stack_pop() - last_operand);
                } else if (strcmp(*argv, "/") == 0) {
                        last_operand = stack_pop();
                        stack_push(stack_pop() / last_operand);
                } else {
                        printf("error: invalid op %s\n", *argv);
                        return 1;
                }
        }
        printf("%g\n", stack_pop());
        return 0;
}

int is_number(char *s) {
        for (; *s != '\0'; s++) if (!isdigit(*s) && *s != '.') return 0;
        return 1;
}

#define STACK_CAPACITY 1000

double stack[STACK_CAPACITY];
double *stack_p = stack;

void stack_push(double x) {
        if (stack + STACK_CAPACITY - stack_p > 0) *stack_p++ = x;
}

double stack_pop() {
        if (stack_p > stack) return *--stack_p;
        else return 0;
}

double stack_top() {
        if (stack_p > stack) return *(stack_p - 1);
        else return 0;
}
