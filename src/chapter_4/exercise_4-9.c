#include <stdio.h>
#include <string.h>

#define UNGETCH_BUFFER_MAX_LENGTH 100

// The original version in the book use char instead of int.
// Which may or may not be signed. Therefore, it may not
// hold the EOF character. int is thus platform-independent.
int ungetch_buffer[UNGETCH_BUFFER_MAX_LENGTH];
int ungetch_buffer_length = 0;

int getch(void);
void ungetch(int c);

int main() {
        ungetch(EOF);
        printf("%d\n", getch());
        return 0;
}

int getch(void) {
        return (ungetch_buffer_length > 0) ?
                ungetch_buffer[--ungetch_buffer_length] :
                getchar();
}

void ungetch(int c) {
        if (ungetch_buffer_length < UNGETCH_BUFFER_MAX_LENGTH)
                ungetch_buffer[ungetch_buffer_length++] = c;
        else printf("error: ungetch buffer limit reached.\n");
}
