// Using multiplication instead of the AND operation can
// solve the problem.
//
// One thing to consider that in multiplication does not
// stop after knowing the truthness of the condition.
// Meaning, even if the first case is false, all the other
// cases will be tested.
//
// This isn't problematic in this case as worst case assumes
// we are calling getchar() after we found EOF, which
// results in getchar() keep returning EOF afterwards. The
// program works as intended.
//
// Usually you should not be using multiplication because of
// the stated reason and prefer && or || when possible.

#include <stdio.h>

#define MAX_LINE_LENGTH 1000

int main() {
        int c, i = 0;
        char s[MAX_LINE_LENGTH];
        for (; (i < MAX_LINE_LENGTH - 1) * ((c = getchar()) != '\n') * (c != EOF); ++i)
                s[i] = c;
        s[i] = '\0';
        printf("%s\n", s);
        return 0;
}
