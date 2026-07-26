#include <stdio.h>

// Many experienced C programmers use do {...} while (0) in
// macros. This is because without them, if you call the
// macro in a if statement like this:
//
//        if (something) swap();
//        else ...code...
//
// the else case will through an error because it will no
// longer be with the if because the lack of {} braces.
//
// Some people would argue about placing braces in the
// macro. In that case, you cannot provide the semicolon
// after swap(), as it would leave the else part outside
// of the if.
//
// Therefore, using a do {...} while (0) fixes those issues
// and lets us use the macro as if it was an ordinary
// function.
//
// I keep the backslashes at column-limit to keep code
// looking clearer.
#define swap(t, x, y)                                                                    \
        do {                                                                             \
                t tmp;                                                                   \
                tmp = x;                                                                 \
                x = y;                                                                   \
                y = tmp;                                                                 \
        } while (0)

int main() {
        int x = 20, y = 30;
        swap(int, x, y);
        printf("%d %d\n", x, y);
        return 0;
}
