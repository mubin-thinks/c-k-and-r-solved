#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_N 10
#define COLUMN_MAX_LENGTH 1000
#define N_MAX 500
#define ALLOC_CAPACITY COLUMN_MAX_LENGTH * N_MAX

int get_line(char *s, int max_length);

int main(int argc, char *argv[]) {
        char *lines_ptr[N_MAX], alloc_buffer[ALLOC_CAPACITY];
        int n = DEFAULT_N;
        for (; --argc && ++argv; ) {
                if (**argv == '-') {
                        n = atoi((*argv) + 1);
                        if (n == 0) {
                                printf("error: n must be positive.\n");
                                return 1;
                        } else if (n > 500) {
                                printf("error: n <= 500.\n");
                                return 1;
                        }
                }
        }
        char **p = lines_ptr, *write_ptr = alloc_buffer, line_length,
              tmp_line[COLUMN_MAX_LENGTH];
        int lines_count = 0;
        for (
                ;
                (line_length = get_line(tmp_line, COLUMN_MAX_LENGTH)) &&
                strncpy(write_ptr, tmp_line, 1000);
                lines_count++,
                write_ptr = alloc_buffer + ((p - lines_ptr) * COLUMN_MAX_LENGTH)
        ) {
                *p = write_ptr;
                *(*p + line_length - 1) = '\0';
                p = lines_ptr + ((lines_count + 1) % n);
        }
        if (lines_count < n) for (int i = 0; i < lines_count; i++)
                printf("%s\n", lines_ptr[i]);
        else for (int i = p - lines_ptr; ; i++) {
                printf("%s\n", *(lines_ptr + (i % n)));
                if (lines_ptr + ((i + 1) % n) == p) break;
        }
        return 0;
}

int get_line(char *s, int max_length) {
        int c;
        char *p = s;
        for (; (c = getchar()) != EOF && c != '\n' && (max_length--) > 2 && (*p++ = c); );
        if (c == '\n') *p++ = c;
        *p = '\0';
        return p - s;
}
