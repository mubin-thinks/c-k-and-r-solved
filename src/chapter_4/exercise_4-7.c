#include <stdio.h>
#include <string.h>

#define UNGETCH_BUFFER_MAX_LENGTH 26

char ungetch_buffer[UNGETCH_BUFFER_MAX_LENGTH];
int ungetch_buffer_length = 0;

int getch(void);
void ungetch(char c);
void ungets(const char s[]);

int main() {
        ungets("test");
        printf("%c", getch());
        printf("%c", getch());
        printf("%c", getch());
        printf("%c\n", getch());
        ungets("other test");
        ungetch_buffer[ungetch_buffer_length] = '\0';
        printf("%s\n", ungetch_buffer);
        return 0;
}

int getch(void) {
        return (ungetch_buffer_length > 0) ?
                ungetch_buffer[--ungetch_buffer_length] :
                getchar();
}

void ungetch(char c) {
        if (ungetch_buffer_length < UNGETCH_BUFFER_MAX_LENGTH)
                ungetch_buffer[ungetch_buffer_length++] = c;
        else printf("error: ungetch buffer limit reached.\n");
}

// Writing directly to buffer is better than using
// ungetch(), reason being we have to run the if statement
// repeatedly which will result in less performance and
// the string will be truncated to maximum the buffer can
// take instead of rejecting the entire string.
void ungets(const char s[]) {
        int n = strlen(s);
        if (ungetch_buffer_length + n <= UNGETCH_BUFFER_MAX_LENGTH)
                for (int i = 0; n--; i++) ungetch_buffer[ungetch_buffer_length++] = s[i];
        else printf("error: ungetch buffer limit reached. did not write to buffer.\n");
}
