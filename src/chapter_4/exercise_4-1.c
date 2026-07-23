#include <stdio.h>
#include <string.h>

int strrindex(const char s[], const char t[]);

int main() {
        printf("%d\n", strrindex("this is a test", "is"));
        printf("%d\n", strrindex("something something something...", "thing"));
        printf("%d\n", strrindex("another test", "r"));
        printf("%d\n", strrindex("", "something"));
        printf("%d\n", strrindex("something", ""));
        return 0;
}

int strrindex(const char s[], const char t[]) {
        int j, k;
        for (int i = strlen(s) - 1; i >= 0; --i) {
                for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++);
                if (k > 0 && t[k] == '\0') return i;
        }
        return -1;
}
