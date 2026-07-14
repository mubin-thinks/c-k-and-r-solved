#include <stdio.h>

#define TRUE 1
#define FALSE 0

int main() {
        int in_string = FALSE;
        for (int c, next_c; (c = getchar()) != EOF; ) {
                if (c == '\\') {
                        putchar(c);
                        putchar(getchar());
                        c = getchar();
                }
                if (in_string == FALSE && c == '/') {
                        next_c = getchar();
                        if (next_c == '*') {
                                while (next_c != EOF && (c != '*' || next_c != '/')) {
                                        c = next_c;
                                        next_c = getchar();
                                }
                        } else if (next_c == '/') {
                                while ((c = getchar()) != EOF && c != '\n');
                                if (c == '\n') putchar(c);
                        } else {
                                putchar(c);
                                putchar(next_c);
                        }
                } else if (c != EOF) putchar(c);
                if (in_string == FALSE && c == '\"') in_string = TRUE;
                else if (in_string == TRUE && c == '\"') in_string = FALSE;
        }
        return 0;
}
