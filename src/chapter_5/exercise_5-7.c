#include <stdio.h>
#include <string.h>

#define OUTPUT_CAPACITY 500
#define ALLOC_CAPACITY 10000

int get_line(char *s, int max_length);
int readlines(char *output[], int output_length, char *buffer, int buffer_length);
void writelines(char *lines[], int lines_length);
void swap(char *v[], int i, int j);
void qsort(char *v[], int l, int r);

int main() {
        char *lines[OUTPUT_CAPACITY], alloc_buffer[ALLOC_CAPACITY];
        int lines_length;
        if (
                (lines_length = readlines(
                        lines,
                        OUTPUT_CAPACITY,
                        alloc_buffer,
                        ALLOC_CAPACITY
                )) >= 0
        ) {
                qsort(lines, 0, lines_length - 1);
                writelines(lines, lines_length);
                return 0;
        } else {
                printf("error: too many lines.\n");
                return 0;
        }
}

int get_line(char *s, int max_length) {
        int c;
        char *p = s;
        for (; (c = getchar()) != EOF && c != '\n' && (max_length--) > 2 && (*p++ = c); );
        if (c == '\n') *p++ = c;
        *p = '\0';
        return p - s;
}

// Passing buffer from main does increase performance due
// to not having to strcpy(...) to save the string to hidden
// alloc buffer. We can write directly to the buffer passed
// by main instead.
int readlines(char *output[], int output_length, char *buffer, int buffer_length) {
        char *p = buffer;
        int line_length, total_lines = 0;
        for (; (line_length = get_line(p, buffer + buffer_length - p)) > 0; ) {
                if (total_lines >= output_length || buffer + buffer_length - p == 0)
                        return -1;
                *(p + line_length - 1) = '\0';
                output[total_lines++] = p;
                p += line_length;
        }
        return total_lines;
}

void writelines(char *lines[], int lines_length) {
        for (; lines_length--; ) printf("%s\n", *lines++);
}

void swap(char *v[], int i, int j) {
        char *tmp = v[i];
        v[i] = v[j];
        v[j] = tmp;
}

void qsort(char *v[], int l, int r) {
        int last;
        if (l >= r) return;
        swap(v, l, (l + r) / 2);
        last = l;
        for (int i = l + 1; i <= r; i++) if (strcmp(v[i], v[l]) < 0) swap(v, ++last, i);
        swap(v, l, last);
        qsort(v, l, last - 1);
        qsort(v, last + 1, r);
}
