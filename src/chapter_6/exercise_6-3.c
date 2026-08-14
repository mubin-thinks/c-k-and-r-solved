#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define WORD_CAPACITY 100
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

struct num_node_t {
        int num;
        struct num_node_t *l, *r;
};

struct word_node_t {
        char *word;
        struct num_node_t *line_numbers;
        struct word_node_t *l, *r;
};

void skip_spaces(void);
int read_word(char *s, int s_len);
int binary_search(const char **strings, int strings_len, const char *s);
void get_frequencies(
        struct word_node_t **output,
        const char **noise_words,
        int noise_words_len,
        char *s,
        int s_len
);
struct num_node_t *num_node_insert(struct num_node_t *node, int num);
void num_node_print(struct num_node_t *node);
void num_node_free(struct num_node_t *root);
struct word_node_t *word_node_insert(
        struct word_node_t *node,
        const char *s,
        int line_number
);
void word_node_print(struct word_node_t *node);
void word_node_free(struct word_node_t *root);

int main() {
        // Source for noise words:
        // https://gist.github.com/sebleier/554280
        const char *noise_words[] = {
                "a", "about", "above", "after", "again", "against", "all", "am", "an",
                "and", "any", "are", "as", "at", "be", "because", "been", "before",
                "being", "below", "between", "both", "but", "by", "can", "did", "do",
                "does", "doing", "don", "down", "during", "each", "few", "for", "from",
                "further", "had", "has", "have", "having", "he", "her", "here", "hers",
                "herself", "him", "himself", "his", "how", "i", "if", "in", "into", "is",
                "it", "its", "itself", "just", "me", "more", "most", "my", "myself", "no",
                "nor", "not", "now", "of", "off", "on", "once", "only", "or", "other",
                "our", "ours", "ourselves", "out", "over", "own", "s", "same", "she",
                "should", "so", "some", "such", "t", "than", "that", "the", "their",
                "theirs", "them", "themselves", "then", "there", "these", "they", "this",
                "those", "through", "to", "too", "under", "until", "up", "very", "was",
                "we", "were", "what", "when", "where", "which", "while", "who", "whom",
                "why", "will", "with", "you", "your", "yours", "yourself", "yourselves",
        };
        struct word_node_t *root = NULL;
        char s[WORD_CAPACITY];
        get_frequencies(&root, noise_words, ARRAY_SIZE(noise_words), s, WORD_CAPACITY);
        word_node_print(root);
        word_node_free(root);
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

void skip_spaces(void) {
        int c;
        for (; (c = getch()) == ' ' || c == '\t'; );
        ungetch(c);
}

int read_word(char *s, int s_len) {
        skip_spaces();
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

int binary_search(const char **strings, int strings_len, const char *s) {
        int l = 0, r = strings_len - 1, m, compare;
        for (; l <= r; ) {
                m = l + (r - l) / 2;
                if ((compare = strcmp(s, strings[m])) > 0) l = m + 1;
                else if (compare < 0) r = m - 1;
                else return m;
        }
        return -1;
}

void get_frequencies(
        struct word_node_t **output,
        const char **noise_words,
        int noise_words_len,
        char *s,
        int s_len
) {
        for (int line_number = 1; (read_word(s, s_len)) != EOF; ) {
                if (s[0] == '\n') line_number++;
                if (!isalpha(s[0])) continue;
                if (binary_search(noise_words, noise_words_len, s) >= 0) continue;
                *output = word_node_insert(*output, s, line_number);
        }
}

struct num_node_t *num_node_insert(struct num_node_t *node, int num) {
        if (node == NULL) {
                node = (struct num_node_t *)malloc(sizeof(struct num_node_t));
                node->num = num;
                node->l = node->r = NULL;
        } else if (num > node->num) node->r = num_node_insert(node->r, num);
        else if (num < node->num) node->l = num_node_insert(node->l, num);
        return node;
}

void num_node_print(struct num_node_t *node) {
        if (node == NULL) return;
        num_node_print(node->l);
        printf("%d ", node->num);
        num_node_print(node->r);
}

void num_node_free(struct num_node_t *root) {
        if (root == NULL) return;
        num_node_free(root->l);
        num_node_free(root->r);
        free(root);
}

struct word_node_t *word_node_insert(
        struct word_node_t *node,
        const char *s,
        int line_number
) {
        int compare;
        if (node == NULL) {
                node = (struct word_node_t *)malloc(sizeof(struct word_node_t));
                node->word = strdup(s);
                node->line_numbers =
                        num_node_insert((node->line_numbers = NULL), line_number);
                node->l = node->r = NULL;
        } else if ((compare = strcmp(s, node->word)) > 0)
                node->r = word_node_insert(node->r, s, line_number);
        else if (compare < 0) node->l = word_node_insert(node->l, s, line_number);
        else node->line_numbers = num_node_insert(node->line_numbers, line_number);
        return node;
}

void word_node_print(struct word_node_t *node) {
        if (node == NULL) return;
        word_node_print(node->l);
        printf("%s: ", node->word);
        num_node_print(node->line_numbers);
        printf("\n");
        word_node_print(node->r);
}

void word_node_free(struct word_node_t *root) {
        if (root == NULL) return;
        word_node_free(root->l);
        word_node_free(root->r);
        num_node_free(root->line_numbers);
        free(root->word);
        free(root);
}
