// This implementation is partially complete due to the
// program treating function names as variables.

// this implementation is partially inspired by
// https://github.com/ohkimur/the-c-programming-language-2nd-edition-solutions

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const char *invalid_variable_names[] = {
        "void", "char", "int", "float", "double", "short", "long", "const"
};

struct var_tree {
        char *s;
        struct var_tree *l, *r;
};

#define TRUE 1
#define FALSE 0
#define MAX_WORD_LENGTH 100
#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))
#define KEYTAB_LENGTH ARRAY_SIZE(keytab)
#define INVALID_VARIABLE_NAMES_LENGTH ARRAY_SIZE(invalid_variable_names)

void get_args(int argc, char **argv, int *n);
int get_word(char *s, int max_len);
void get_variable_in_tree(
        char *s,
        int max_len,
        const char **invalid_variable_names,
        int invalid_variable_names_len,
        struct var_tree **node
);
struct var_tree *tree_insert(struct var_tree *node, const char *s);
void tree_print_in_groups(struct var_tree *node, int n);
void tree_free(struct var_tree *root);

int main(int argc, char **argv) {
        int n = 6;
        get_args(argc, argv, &n);
        char s[MAX_WORD_LENGTH];
        struct var_tree *root = NULL;
        get_variable_in_tree(
                s,
                MAX_WORD_LENGTH,
                invalid_variable_names,
                INVALID_VARIABLE_NAMES_LENGTH,
                &root
        );
        tree_print_in_groups(root, n);
        tree_free(root);
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
        return isspace(c);
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

int does_literals_begin(void) {
        int c = getch();
        ungetch(c);
        return c == '\'' || c == '\"';
}

void skip_spaces(void) {
        int c;
        for (; isspace(c = getch()); );
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

void skip_literals_in_range(char l, char r) {
        int c = getch();
        if (c != l) {
                ungetch(c);
                return;
        }
        for (; (c = getch()) != r; ) if (c == '\\') getch();
}

void skip_string_literals(void) {
        skip_literals_in_range('\"', '\"');
}

void skip_char_literals(void) {
        skip_literals_in_range('\'', '\'');
}

void get_args(int argc, char **argv, int *n) {
        const char *program_name = *argv;
        for (; --argc && *(*(++argv)) == '-'; ) {
                if ((*n = atoi((*argv) + 1)) == 0) {
                        printf(
                                "%s -<n>\n"
                                "error: please provide positive integer.\n",
                                program_name
                        );
                        exit(1);
                }
        }
}

int get_word(char *s, int max_len) {
        for (; does_spaces_begin() || does_comments_begin() || does_literals_begin(); ) {
                skip_spaces();
                skip_comments();
                skip_string_literals();
                skip_char_literals();
        }
        int c = getch();
        char *w = s;
        *w++ = c;
        max_len--;
        if (!isalpha(c) && c != '_' && c != '#') {
                *w = '\0';
                return c;
        }
        for (; max_len-- && (isalnum(c = getch()) || c == '_'); ) *w++ = c;
        ungetch(c);
        *w = '\0';
        return s[0];
}

int token_is_type(
        const char **invalid_variable_names,
        int invalid_variable_names_len,
        char *s
) {
        for (
                ;
                invalid_variable_names_len && strcmp(s, *invalid_variable_names) != 0;
                invalid_variable_names++, invalid_variable_names_len--
        );
        return invalid_variable_names_len ? 1 : 0;
}

void get_variable_in_tree(
        char *s,
        int max_len,
        const char **invalid_variable_names,
        int invalid_variable_names_len,
        struct var_tree **node
) {
        char in_var_creation = FALSE, take_variable = FALSE;
        for (; get_word(s, max_len) != EOF; ) {
                if (s[0] == ';' || s[0] == '{') in_var_creation = FALSE;
                else if (s[0] == ',') take_variable = TRUE;
                else if (
                        token_is_type(
                                invalid_variable_names,
                                invalid_variable_names_len,
                                s
                        )
                ) {
                        in_var_creation = take_variable = TRUE;
                        continue;
                } else if (strcmp(s, "struct") == 0) {
                        get_word(s, max_len);
                        in_var_creation = take_variable = TRUE;
                        continue;
                }
                if (in_var_creation && !take_variable) continue;
                if (in_var_creation && take_variable && isalpha(s[0])) {
                        *node = tree_insert(*node, s);
                        take_variable = FALSE;
                }
        }
}

struct var_tree *tree_insert(struct var_tree *node, const char *s) {
        int compare;
        if (node == NULL) {
                node = (struct var_tree *)malloc(sizeof(struct var_tree));
                node->s = strdup(s);
                node->l = node->r = NULL;
        } else if ((compare = strcmp(s, node->s)) > 0) node->r = tree_insert(node->r, s);
        else if (compare < 0) node->l = tree_insert(node->l, s);
        return node;
}

void tree_print_in_groups(struct var_tree *node, int n) {
        static char *p = NULL;
        if (node == NULL) return;
        tree_print_in_groups(node->l, n);
        if (p && strncmp(p, node->s, n) != 0) printf("\n");
        p = node->s;
        printf("%s\n", node->s);
        tree_print_in_groups(node->r, n);
}

void tree_free(struct var_tree *root) {
        if (root == NULL) return;
        tree_free(root->l);
        tree_free(root->r);
        free(root);
}
