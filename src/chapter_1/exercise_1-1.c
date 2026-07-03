// gcc error when deleting "main" from "int main()":
//         exercise_1-1.c:49:6: error: expected identifier or ‘(’ before ‘)’ token
//             49 | int () {
//                |      ^
//
// gcc error when deleteing "()" from "int main()":
//         exercise_1-1.c:49:10: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’
//                 before ‘{’ token
//            49 | int main {
//
// gcc error when deleting "{" from "int main() {":
//         exercise_1-1.c: In function ‘main’:
//         exercise_1-1.c:50:9: error: expected declaration specifiers before ‘printf’
//            50 |         printf("Hello, world");
//               |         ^~~~~~
//         exercise_1-1.c:51:9: error: expected declaration specifiers before ‘return’
//            51 |         return 0;
//               |         ^~~~~~
//         exercise_1-1.c:52:1: error: expected declaration specifiers before ‘}’ token
//            52 | }
//               | ^
//         exercise_1-1.c:53: error: expected ‘{’ at end of input
//
// gcc error when removing quotes from "printf("Hello, world");":
//        exercise_1-1.c: In function ‘main’:
//        exercise_1-1.c:50:16: error: ‘Hello’ undeclared (first use in this function);
//                did you mean ‘ftello’?
//           50 |         printf(Hello, world);
//              |                ^~~~~
//              |                ftello
//        exercise_1-1.c:50:16: note: each undeclared identifier is reported only once for
//                each function it appears in
//        exercise_1-1.c:50:23: error: ‘world’ undeclared (first use in this function)
//           50 |         printf(Hello, world);
//              |                       ^~~~~
//
// gcc error when removing ';' from "printf("Hello, world");":
//        exercise_1-1.c: In function ‘main’:
//        exercise_1-1.c:50:31: error: expected ‘;’ before ‘return’
//           50 |         printf("Hello, world")
//              |                               ^
//              |                               ;
//           51 |         return 0;
//              |         ~~~~~~


#include <stdio.h>

int main() {
        printf("Hello, world");
        return 0;
}
