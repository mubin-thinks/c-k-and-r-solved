#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define WORD_CAPACITY 100
#define WORD_ARRAY_CAPACITY 10000

struct word_node_t {
        char *word;
        int count;
        struct word_node_t *l, *r;
};

struct word_array_t {
        char *word;
        int count;
};

void skip_blanks();
int read_word(char *s, int s_len);
void get_frequencies(struct word_node_t **node, char *s, int s_len);
void quick_sort(void *v, int l, int r, int (*compare_fn)(void *a, void *b));
struct word_node_t *word_node_insert(struct word_node_t *node, const char *s);
void word_node_to_array(
        struct word_node_t *node,
        struct word_array_t *array,
        int array_capacity,
        int *array_index
);
void word_node_free(struct word_node_t *root);
void word_array_print(struct word_array_t *array, int array_len);
int word_array_compare(const void *a, const void *b);

int main() {
        char s[WORD_CAPACITY];
        struct word_node_t *words = NULL;
        struct word_array_t words_arr[WORD_ARRAY_CAPACITY];
        get_frequencies(&words, s, WORD_CAPACITY);
        int array_index = 0;
        word_node_to_array(words, words_arr, WORD_ARRAY_CAPACITY, &array_index);
        qsort(words_arr, array_index, sizeof(struct word_array_t), word_array_compare);
        word_array_print(words_arr, array_index);
        word_node_free(words);
        return 0;
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

void skip_blanks(void) {
        int c;
        for (; isspace(c = getch()); );
        ungetch(c);
}

int read_word(char *s, int s_len) {
        skip_blanks();
        int c = getch();
        char *w = s;
        *w++ = c;
        s_len--;
        if (!isalpha(c)) {
                *w = '\0';
                return c;
        }
        for (; s_len-- > 1 && (c = getch()) != EOF && isalpha(c); ) *w++ = c;
        if (c != EOF) ungetch(c);
        *w = '\0';
        return s[0];
}

void get_frequencies(struct word_node_t **node, char *s, int s_len) {
        for (; read_word(s, s_len) != EOF; ) {
                if (!isalpha(s[0])) continue;
                *node = word_node_insert(*node, s);
        }
}

struct word_node_t *word_node_insert(struct word_node_t *node, const char *s) {
        int compare;
        if (node == NULL) {
                node = (struct word_node_t *)malloc(sizeof(struct word_node_t));
                node->word = strdup(s);
                node->count = 1;
                node->l = node->r = NULL;
        } else if ((compare = strcmp(s, node->word)) > 0)
                node->r = word_node_insert(node->r, s);
        else if (compare < 0) node->l = word_node_insert(node->l, s);
        else node->count++;
        return node;
}

void word_node_to_array(
        struct word_node_t *node,
        struct word_array_t *array,
        int array_capacity,
        int *array_index
) {
        if (node == NULL) return;
        word_node_to_array(node->l, array, array_capacity, array_index);
        if (*array_index < array_capacity) {
                array[*array_index].word = node->word;
                array[(*array_index)++].count = node->count;
        }
        word_node_to_array(node->r, array, array_capacity, array_index);
}

void word_node_free(struct word_node_t *root) {
        if (root == NULL) return;
        word_node_free(root->l);
        word_node_free(root->r);
        free(root->word);
        free(root);
}

void word_array_print(struct word_array_t *array, int array_len) {
        for (; array_len; array_len--, array++)
                printf("%d %s\n", array->count, array->word);
}

int word_array_compare(const void *a, const void *b) {
        return (*(const struct word_array_t *)b).count -
                (*(const struct word_array_t *)a).count;
}
