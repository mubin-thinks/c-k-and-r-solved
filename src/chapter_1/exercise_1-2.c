// gcc error:
//         exercise_1-2.c: In function ‘main’:
//         exercise_1-2.c:10:32: warning: unknown escape sequence: ‘\c’
//             10 |         printf("Hello, world\c");
//                |                                ^

#include <stdio.h>

int main() {
        printf("Hello, world\c");
        return 0;
}
