#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define WORD_CAPACITY 100
#define HASH_LIST_CAPACITY 100

struct hash_list_t {
        char *key, *value;
        struct hash_list_t *next;
};

struct hash_list_t *hash_list_table[HASH_LIST_CAPACITY];

void skip_spaces(void);
void read_until(char *s, int s_len, char t);
int read_word(char *s, int s_len);
int preprocess_from_stdin(char *s, int s_len);
unsigned int hash_list_hash(const char *key);
struct hash_list_t *hash_list_lookup(const char *key);
struct hash_list_t *hash_list_insert(const char *key, const char *value);
void hash_list_free();

int main() {
        char s[WORD_CAPACITY];
        preprocess_from_stdin(s, WORD_CAPACITY);
        return 0;
}

#define UNGETCH_BUFFER_CAPACITY 300

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

int does_spaces_begin(void) {
        int c = getch();
        ungetch(c);
        return c == ' ' || c == '\t';
}

int does_comments_begin(void) {
        int c = getch();
        if (c != '/') {
                ungetch(c);
                return 0;
        }
        if ((c = getch()) != '/' && c != '*') {
                ungetch(c);
                ungetch('/');
                return 0;
        }
        ungetch(c);
        ungetch('/');
        return 1;
}

void skip_spaces(void) {
        int c;
        for (; (c = getch()) == ' ' || c == '\t'; );
        ungetch(c);
}

void skip_comments(void) {
        if (!does_comments_begin()) return;
        getch();
        int c = getch(), next_c;
        if (c == '/') for (; (c = getch()) != EOF && c != '\n'; );
        else if (c == '*') {
                for (
                        c = getch();
                        (next_c = getch()) != EOF && (c != '*' || next_c != '/');
                ) c = next_c;
        }
}

void print_literals_in_range(char l, char r) {
        int c = getch();
        if (c != l) {
                ungetch(c);
                return;
        }
        putchar(c);
        for (; (c = getch()) != r; ) putchar(c);
        putchar(c);
}

void read_until(char *s, int s_len, char t) {
        skip_spaces();
        int c;
        for (; s_len-- > 1 && (c = getch()) != EOF && c != t; ) *s++ = c;
        *s = '\0';
}

int read_word(char *s, int s_len) {
        for (; does_comments_begin(); ) skip_comments();
        int c = getch();
        char *w = s;
        *w++ = c;
        s_len--;
        if (!isalpha(c) && c != '_' && c != '#') {
                *w = '\0';
                return c;
        }
        for (; s_len-- > 1 && (isalnum(c = getch()) || c == '_'); ) *w++ = c;
        ungetch(c);
        *w = '\0';
        return s[0];
}

int preprocess_from_stdin(char *s, int s_len) {
        char *tmp = (char *)malloc(s_len * sizeof(char));
        struct hash_list_t *item;
        for (; read_word(s, s_len) != EOF; ) {
                if (s[0] == '\"') {
                        ungetch('\"');
                        print_literals_in_range('\"', '\"');
                        continue;
                }
                else if (s[0] == '\'') {
                        ungetch('\'');
                        print_literals_in_range('\'', '\'');
                        continue;
                }
                if (strcmp(s, "#define") != 0) {
                        if (item = hash_list_lookup(s)) printf("%s", item->value);
                        else printf("%s", s);
                        continue;
                }
                skip_spaces();
                read_word(tmp, s_len);
                read_until(s, s_len, '\n');
                if (s[0] == '(') {
                        printf("#define %s%s\n", tmp, s);
                        continue;
                }
                hash_list_insert(tmp, s);
        }
        free(tmp);
        hash_list_free();
}

unsigned int hash_list_hash(const char *key) {
        unsigned int result = 0;
        for (; *key != '\0'; key++) result = *key + 31 * result;
        return result % HASH_LIST_CAPACITY;
}

struct hash_list_t *hash_list_lookup(const char *key) {
        struct hash_list_t *item = hash_list_table[hash_list_hash(key)];
        for (; item != NULL; item = item->next) if (strcmp(key, item->key) == 0) break;
        return item;
}

struct hash_list_t *hash_list_insert(const char *key, const char *value) {
        struct hash_list_t *item;
        unsigned int hash_value;
        if ((item = hash_list_lookup(key)) == NULL) {
                item = (struct hash_list_t *)malloc(sizeof(struct hash_list_t));
                if (item == NULL || (item->key = strdup(key)) == NULL) return NULL;
                hash_value = hash_list_hash(key);
                item->next = hash_list_table[hash_value];
                hash_list_table[hash_value] = item;
        } else free(item->value);
        if ((item->value = strdup(value)) == NULL) return NULL;
        return item;
}

void hash_list_free() {
        for (int i = 0; i < HASH_LIST_CAPACITY; i++) {
                if (hash_list_table[i] == NULL) continue;
                for (
                        struct hash_list_t *item = hash_list_table[i], *tmp = item->next;
                        item != NULL;
                        item = tmp, tmp = (tmp) ? tmp->next : NULL
                ) {
                        free(item->key);
                        free(item->value);
                        free(item);
                }
                hash_list_table[i] = NULL;
        }
}
