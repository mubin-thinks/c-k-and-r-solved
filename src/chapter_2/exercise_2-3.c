#include <stdio.h>
#include <string.h>
#include <ctype.h>

int int_from_hex_char(char c);
int htoi(char s[]);

int main() {
        printf("                     hex                int\n");
        printf("-------------------------------------------\n");
        printf("%24s   %16d\n", "0xabcdef", htoi("0xabcdef"));
        printf("%24s   %16d\n", "0x123456", htoi("0x123456"));
        printf("%24s   %16d\n", "0X7FFFFFFF", htoi("0X7FFFFFFF"));
        printf("%24s   %16d\n", "7a", htoi("7a"));
        printf("%24s   %16d\n", "1a2b3c", htoi("1a2b3c"));
        printf("%24s   %16d\n", "should_be_nothing", htoi("should_be_nothing"));
        return 0;
}

int int_from_hex_char(char c) {
        if (c >= '0' && c <= '9') return c - '0';
        if (c >= 'a' && c <= 'f') return c - 'a' + 10;
        if (c >= 'A' && c <= 'F') return c - 'A' + 10;
}

int htoi(char s[]) {
        int n = strlen(s), i = 0, result = 0;
        if (n >= 2 && s[0] == '0' && tolower(s[1]) == 'x') i = 2;
        for (
                ;
                (s[i] >= '0' && s[i] <= '9') ||
                (s[i] >= 'a' && s[i] <= 'f') ||
                (s[i] >= 'A' && s[i] <= 'F');
                ++i
        ) result = 16 * result + int_from_hex_char(s[i]);
        return result;
}
