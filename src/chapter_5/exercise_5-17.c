// example:
//        $ gcc -o sort_tables exercise_5-17.c
//
//        $ cat input.txt
//        test 234 12.32424 w
//        abcd 721 12.631 x
//        another_test 215 32.32 y
//        another_test 216 72.32 z
//
//        $ cat input.txt | ./sort_tables -1f -2n -3nr -4r
//                   abcd             215           72.32               z
//           another_test             216           32.32               y
//           another_test             234          12.631               x
//                   test             721        12.32424               w

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FIELD_CAPACITY 50
#define LINES_PER_FIELD 1000
#define LINES_CAPACITY FIELD_CAPACITY * LINES_PER_FIELD
#define ALLOC_CAPACITY 20000
#define max(a, b) ((a) > (b) ? (a) : (b))

int getch(void);
void ungetch(char c);
int get_token(char *s, int max_length);
int read_fields(
        char **fields_ptr[],
        int fields_ptr_length,
        char *lines_ptr[],
        int lines_ptr_length,
        int lines_per_field,
        int *total_lines,
        char *buffer,
        int buffer_length
);
void write_fields(char **fields_ptr[], int total_fields, int total_lines);
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
int strcmp_dir(const char *a, const char *b, int fold);

int main(int argc, char **argv) {
        int n[FIELD_CAPACITY], r[FIELD_CAPACITY], f[FIELD_CAPACITY], d[FIELD_CAPACITY],
                field_indicies[FIELD_CAPACITY], operating_fields_count = 0;
        char num_as_string[10];
        memset(n, 0, FIELD_CAPACITY);
        memset(r, 0, FIELD_CAPACITY);
        memset(f, 0, FIELD_CAPACITY);
        memset(d, 0, FIELD_CAPACITY);
        for (; --argc && **++argv == '-'; ) {
                for (char c; c = *(++(*argv)); ) {
                        if (isdigit(c)) {
                                int i = 0;
                                num_as_string[i++] = c;
                                for (; isdigit(*((*argv) + 1)); )
                                        num_as_string[i++] = *(++(*argv));
                                num_as_string[i] = '\0';
                                int possible_field_index = atoi(num_as_string);
                                if (
                                        possible_field_index <= 0 ||
                                        possible_field_index > 50
                                ) {
                                        printf(
                                                "error: field index %d out of range.\n",
                                                possible_field_index
                                        );
                                        return 1;
                                }
                                field_indicies[operating_fields_count] =
                                        possible_field_index;
                        } else if (c == 'n') n[operating_fields_count] = 1;
                        else if (c == 'r') r[operating_fields_count] = 1;
                        else if (c == 'f') f[operating_fields_count] = 1;
                        else if (c == 'd') d[operating_fields_count] = 1;
                        else {
                                printf("error: unknown option '%c'.\n", c);
                                return 1;
                        }
                }
                operating_fields_count++;
        }
        char **fields_ptr[FIELD_CAPACITY], *lines_ptr[LINES_CAPACITY],
                alloc_buffer[ALLOC_CAPACITY];
        int total_fields, total_lines;
        if (
                (total_fields = read_fields(
                        fields_ptr,
                        FIELD_CAPACITY,
                        lines_ptr,
                        LINES_CAPACITY,
                        LINES_PER_FIELD,
                        &total_lines,
                        alloc_buffer,
                        ALLOC_CAPACITY
                )) >= 0
        ) {
                for (int i = 0; i < operating_fields_count; i++) {
                        quick_sort(
                                (void**)(*(fields_ptr + field_indicies[i] - 1)),
                                0,
                                total_lines - 1,
                                (int (*)(void*, void*, int))((n[i]) ? numcmp :
                                        ((d[i]) ? strcmp_dir : strcmp_optionally_folded)),
                                r[i],
                                f[i]
                        );
                }
                write_fields(fields_ptr, total_fields, total_lines);
                return 0;
        } else {
                printf("error: too many lines.\n");
                return 0;
        }
}

#define UNGETCH_BUFFER_CAPACITY 100

char ungetch_buffer[UNGETCH_BUFFER_CAPACITY];
char *ungetch_buffer_p = ungetch_buffer;

int getch(void) {
        return (ungetch_buffer_p > ungetch_buffer) ? *--ungetch_buffer_p : getchar();
}

void ungetch(char c) {
        if (ungetch_buffer + UNGETCH_BUFFER_CAPACITY - ungetch_buffer_p > 0)
                *ungetch_buffer_p++ = c;
        else printf("error: ungetch buffer limit reached.\n");
}

int get_token(char *s, int max_length) {
        char *p = s;
        int c;
        for (; (c = getch()) == ' ' || c == '\t'; );
        for (; p - s < max_length - 2 && !isspace(c) && c != EOF; c = getch()) *p++ = c;
        if (c == '\n') *p++ = c;
        else if (c != EOF) ungetch(c);
        *p = '\0';
        return p - s;
}

int read_fields(
        char **fields_ptr[],
        int fields_ptr_length,
        char *lines_ptr[],
        int lines_ptr_length,
        int lines_per_field,
        int *total_lines,
        char *buffer,
        int buffer_length
) {
        *total_lines = 0;
        int total_fields = -1;
        char **p = lines_ptr, *write_ptr = buffer, line_length;
        for (int i = 0; i < fields_ptr_length; i++)
                *fields_ptr++ = lines_ptr + (i * lines_per_field);
        for (
                int i = 0;
                (line_length = get_token(
                        write_ptr,
                        buffer + buffer_length - write_ptr
                )) > 0;
        ) {
                *(p + (i * lines_per_field)) = write_ptr;
                if (write_ptr[line_length - 1] == '\n') {
                        total_fields = max(total_fields, i);
                        write_ptr[--line_length] = '\0';
                        (*total_lines)++;
                        p++;
                        i = 0;
                } else i++;
                write_ptr += line_length + 1;
        }
        return total_fields + 1;
}

void write_fields(char **fields_ptr[], int total_fields, int total_lines) {
        for (int i = 0; i < total_fields * total_lines; i++) {
                printf(
                        "%15s ",
                        *(*(fields_ptr + (i % total_fields)) + (i / total_fields))
                );
                if ((i + 1) % total_fields == 0) putchar('\n');
        }
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
        for (; *a && *b && ((fold) ? tolower(*a) == tolower(*b) : *a == *b); a++, b++);
        return (fold) ? tolower(*a) - tolower(*b) : *a - *b;
}

int numcmp(const char *a, const char *b, int fold) {
        double c = atof(a), d = atof(b);
        if (c > d) return 1;
        if (c < d) return -1;
        return 0;
}

int dir_char(char c) {
        if (
                (c >= 'a' && c <= 'z') ||
                (c >= 'A' && c <= 'Z') ||
                (c >= '0' && c <= '9') ||
                c == ' '
        ) return 1;
        return 0;
}

int strcmp_dir(const char *a, const char *b, int fold) {
        for (
                ;
                *a &&
                *b &&
                ((!dir_char(*a) || !dir_char(*b)) ||
                ((fold) ? tolower(*a) == tolower(*b) : *a == *b));
                a++, b++
        );
        return (fold) ? tolower(*a) - tolower(*b) : *a - *b;
}
