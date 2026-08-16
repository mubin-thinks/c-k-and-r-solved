#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_LIST_CAPACITY 100

struct hash_list_t {
        char *key, *value;
        struct hash_list_t *next;
};

struct hash_list_t *hash_list_table[HASH_LIST_CAPACITY];

unsigned int hash_list_hash(const char *key);
struct hash_list_t *hash_list_lookup(const char *key);
struct hash_list_t *hash_list_insert(const char *key, const char *value);
void hash_list_undef(const char *key);
void hash_list_print_all();
void hash_list_free();

int main() {
        hash_list_insert("test", "123");
        hash_list_insert("3274", "123");
        hash_list_insert("621934", "123");
        hash_list_insert("something", "123");
        hash_list_insert("another test", "123");
        hash_list_insert("another test", "something different");
        hash_list_insert("abcdefgh", "ijklmnop");
        hash_list_insert("12345678", "98765432");
        hash_list_insert("this text is intentionally long for testing", "98765432");
        hash_list_undef("abcdefgh");
        hash_list_undef("this text is intentionally long for testing");
        hash_list_print_all();
        hash_list_free();
        return 0;
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

void hash_list_undef(const char *key) {
        unsigned int hash_value = hash_list_hash(key);
        struct hash_list_t *last = NULL, *current = hash_list_table[hash_value];
        for (; current != NULL; last = current, current = current->next)
                if (strcmp(key, current->key) == 0) break;
        if (current == NULL) return;
        if (last == NULL) hash_list_table[hash_value] = NULL;
        else last->next = current->next;
        free(current);
}

void hash_list_print_all() {
        for (int i = 0; i < HASH_LIST_CAPACITY; i++) {
                if (hash_list_table[i] == NULL) continue;
                printf("hash_list_table[%5d] -> ", i);
                for (
                        struct hash_list_t *item = hash_list_table[i];
                        item != NULL;
                        item = item->next
                ) printf("(%s, %s) -> ", item->key, item->value);
                printf("(nil)\n");
        }
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
