#include <stdio.h>
#include <string.h>
#include <ctype.h>

void parse_arguments(char *p, int *is_lower);
void print_output(int is_lower);

int main(int argc, char **argv) {
        int is_lower;
        parse_arguments(*argv, &is_lower);
        if (is_lower == -1) {
                printf("error: expected program name lower or upper.\n");
                return 1;
        }
        print_output(is_lower);
        return 0;
}

void parse_arguments(char *p, int *is_lower) {
        for (; !isalnum(*p); p++);
        if (strcmp(p, "lower") == 0) *is_lower = 1;
        else if (strcmp(p, "upper") == 0) *is_lower = 0;
        else *is_lower = -1;
}

void print_output(int is_lower) {
        int (*fn)(int ch) = (is_lower) ? tolower : toupper;
        for (int c; (c = getchar()) != EOF; ) printf("%c", (*fn)(c));
}
