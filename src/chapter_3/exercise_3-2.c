#include <stdio.h>
#include <string.h>

void escape(char s[], const char t[]);
void unescape(char s[], const char t[]);

int main() {
        char s[1000], t[500];

        strcpy(t, "\n\n\n\ta message\t\t\t\n\a\b\f\n\r\t\v\\\?\'\"\n");
        escape(s, t);
        printf("%s\n", s);

        strcpy(t, "a message\\n\\tanother message\\n");
        unescape(s, t);
        printf("%s", s);

        strcpy(t, "a\nb\n\t\b\ac\d\e\f\g\hd");
        escape(s, t);
        printf("%s\n", s);

        strcpy(t, "a\\t\\tb\\n\\nc\v\vd\?\?");
        unescape(s, t);
        printf("%s\n", s);
        return 0;
}

void escape(char s[], const char t[]) {
        int i = 0, j = 0;
        for (char c; t[i] != '\0'; i++) {
                switch (t[i]) {
                case '\a': case '\b': case '\f': case '\n': case '\r': case '\t':
                case '\v': case '\\': case '\?': case '\'': case '\"':
                        s[j++] = '\\';
                        if (t[i] == '\a') c = 'a';
                        else if (t[i] == '\b') c = 'b';
                        else if (t[i] == '\f') c = 'f';
                        else if (t[i] == '\n') c = 'n';
                        else if (t[i] == '\r') c = 'r';
                        else if (t[i] == '\t') c = 't';
                        else if (t[i] == '\v') c = 'v';
                        else if (t[i] == '\\') c = '\\';
                        else if (t[i] == '\?') c = '\?';
                        else if (t[i] == '\'') c = '\'';
                        else if (t[i] == '\"') c = '\"';
                        s[j++] = c;
                        break;
                default:
                        s[j++] = t[i];
                        break;
                }
        }
        s[j] = '\0';
}

void unescape(char s[], const char t[]) {
        int i = 0, j = 0;
        for (char c, next_c; t[i] != '\0'; i++) {
                switch (t[i]) {
                case '\\':
                        next_c = t[++i];
                        if (next_c == '\0') break;
                        if (
                                next_c != 'a' && next_c != 'b' && next_c != 'f' &&
                                next_c != 'n' && next_c != 'r' && next_c != 't' &&
                                next_c != 'v' && next_c != '\\' && next_c != '\?' &&
                                next_c != '\'' && next_c != '\"'
                        ) {
                                s[j++] = '\\';
                                s[j++] = next_c;
                        } else {
                                if (next_c == 'a') c = '\a';
                                else if (next_c == 'b') c = '\b';
                                else if (next_c == 'f') c = '\f';
                                else if (next_c == 'n') c = '\n';
                                else if (next_c == 'r') c = '\r';
                                else if (next_c == 't') c = '\t';
                                else if (next_c == 'v') c = '\v';
                                else if (next_c == '\\') c = '\\';
                                else if (next_c == '\?') c = '\?';
                                else if (next_c == '\'') c = '\'';
                                else if (next_c == '\"') c = '\"';
                                s[j++] = c;
                        }
                        break;
                default:
                        s[j++] = t[i];
                        break;
                }
        }
        s[j] = '\0';
}
