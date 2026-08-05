#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define OUTPUT_CAPACITY 500
#define ALLOC_CAPACITY 10000

int get_line(char *s, int max_length);
int readlines(char *output[], int output_length, char *buffer, int buffer_length);
void writelines(char *lines[], int lines_length);
void swap(void *v[], int i, int j);
void quick_sort(
        void *v[],
        int l,
        int r,
        int (*comp)(void *a, void *b, int fold),
        int reverse,
        int fold
);
int strcmp_optionally_folded(const char *a, const char *b, int fold);
int numcmp(const char *a, const char *b, int fold);

int main(int argc, char **argv) {
        int n = 0, r = 0, f = 0;
        for (; --argc && **++argv == '-'; ) for (char c; c = *++(*argv); ) {
                if (c == 'n') n = 1;
                else if (c == 'r') r = 1;
                else if (c == 'f') f = 1;
                else {
                        printf("error: unknown option %c\n", c);
                        return 1;
                }
        }
        char *lines_ptr[OUTPUT_CAPACITY], alloc_buffer[ALLOC_CAPACITY];
        int lines_ptr_length;
        if (
                (lines_ptr_length = readlines(
                        lines_ptr,
                        OUTPUT_CAPACITY,
                        alloc_buffer,
                        ALLOC_CAPACITY
                )) >= 0
        ) {
                quick_sort(
                        (void**)lines_ptr,
                        0,
                        lines_ptr_length - 1,
                        (int (*)(void*, void*, int))((n) ? numcmp :
                                strcmp_optionally_folded),
                        r,
                        f
                );
                writelines(lines_ptr, lines_ptr_length);
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

void swap(void *v[], int i, int j) {
        void *tmp = v[i];
        v[i] = v[j];
        v[j] = tmp;
}

void quick_sort(
        void *v[],
        int l,
        int r,
        int (*comp)(void *a, void *b, int fold),
        int reverse,
        int fold
) {
        int last;
        if (l >= r) return;
        swap(v, l, (l + r) / 2);
        last = l;
        int comp_result;
        for (int i = l + 1; i <= r; i++) {
                comp_result = reverse ? (*comp)(v[i], v[l], fold) > 0 :
                        (*comp)(v[i], v[l], fold) < 0;
                if (comp_result) swap(v, ++last, i);
        }
        swap(v, l, last);
        quick_sort(v, l, last - 1, comp, reverse, fold);
        quick_sort(v, last + 1, r, comp, reverse, fold);
}

int strcmp_optionally_folded(const char *a, const char *b, int fold) {
        for (; ((fold) ? tolower(*a) == tolower(*b) : *a == *b) && *a; a++, b++);
        return (fold) ? tolower(*a) - tolower(*b) : *a - *b;
}

int numcmp(const char *a, const char *b, int fold) {
        double c = atof(a), d = atof(b);
        if (c > d) return 1;
        if (c < d) return -1;
        return 0;
}
