#include <stdio.h>

char lower(char c);

int main() {
        printf("%c\n", lower('A'));
        printf("%c\n", lower('b'));
        printf("%c\n", lower('0'));
        printf("%c\n", lower('2'));
        printf("%c\n", lower('K'));
        printf("%c\n", lower('`'));
        printf("%c\n", lower('~'));
        return 0;
}

char lower(char c) {
        return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c;
}
