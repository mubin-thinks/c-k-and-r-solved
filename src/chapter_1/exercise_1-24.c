#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define MAX_ESCAPE_SEQUENCE_ERROR_STORAGE 100
#define SPACES_FOR_A_TAB "        "

int main() {
        // () {} [] <> \x "" ''
        int rounded_brackets_equality = 0, curly_brackets_equality = 0,
                square_brackets_equality = 0, angle_brackets_equality = 0,
                excess_closing_rounded_brackets = 0, excess_closing_curly_brackets = 0,
                excess_closing_square_brackets = 0, excess_closing_angle_brackets = 0,
                in_double_quotes = FALSE, in_single_quotes = FALSE;
        char invalid_escape_sequences[MAX_ESCAPE_SEQUENCE_ERROR_STORAGE];
        int invalid_escape_sequences_length = 0;

        for (int c; (c = getchar()) != EOF; ) {
                if (c == '\\') {
                        c = getchar();
                        if (
                                c != 'a' && c != 'b' && c != 'f' && c != 'n' &&
                                c != 'r' && c != 't' && c != 'v' && c != '\\' &&
                                c != '?' && c != '\'' && c != '\"' &&
                                invalid_escape_sequences_length <
                                        MAX_ESCAPE_SEQUENCE_ERROR_STORAGE
                        ) {
                                invalid_escape_sequences[invalid_escape_sequences_length]
                                        = c;
                                ++invalid_escape_sequences_length;
                        }
                } else if (c == '(') ++rounded_brackets_equality;
                else if (c == ')') {
                        --rounded_brackets_equality;
                        if (rounded_brackets_equality < 0) {
                                rounded_brackets_equality = 0;
                                excess_closing_rounded_brackets++;
                        }
                } else if (c == '{') ++curly_brackets_equality;
                else if (c == '}') {
                        --curly_brackets_equality;
                        if (curly_brackets_equality < 0) {
                                curly_brackets_equality = 0;
                                excess_closing_curly_brackets++;
                        }
                } else if (c == '[') ++square_brackets_equality;
                else if (c == ']') {
                        --square_brackets_equality;
                        if (square_brackets_equality < 0) {
                                square_brackets_equality = 0;
                                excess_closing_square_brackets++;
                        }
                } else if (c == '<') ++angle_brackets_equality;
                else if (c == '>') {
                        --angle_brackets_equality;
                        if (angle_brackets_equality < 0) {
                                angle_brackets_equality = 0;
                                excess_closing_angle_brackets++;
                        }
                } else if (c == '\"') {
                        if (in_double_quotes == FALSE) in_double_quotes = TRUE;
                        else in_double_quotes = FALSE;
                } else if (c == '\'') {
                        if (in_single_quotes == FALSE) in_single_quotes = TRUE;
                        else in_single_quotes = FALSE;
                }
        }

        if (
                rounded_brackets_equality > 0 || excess_closing_rounded_brackets > 0 ||
                curly_brackets_equality > 0 || excess_closing_curly_brackets > 0 ||
                square_brackets_equality > 0 || excess_closing_square_brackets > 0 ||
                angle_brackets_equality > 0 || excess_closing_angle_brackets > 0 ||
                in_double_quotes == TRUE || in_single_quotes == TRUE ||
                invalid_escape_sequences_length > 0
        ) printf("errors:\n");

        if (rounded_brackets_equality > 0) {
                printf(
                        "%s- %d excessive \'(\' brackets\n",
                        SPACES_FOR_A_TAB,
                        rounded_brackets_equality
                );
        }
        if (excess_closing_rounded_brackets > 0) {
                printf(
                        "%s- %d excessive \')\' brackets\n",
                        SPACES_FOR_A_TAB,
                        excess_closing_rounded_brackets
                );
        }
        if (curly_brackets_equality > 0) {
                printf(
                        "%s- %d excessive \'{\' brackets\n",
                        SPACES_FOR_A_TAB,
                        curly_brackets_equality
                );
        }
        if (excess_closing_curly_brackets > 0) {
                printf(
                        "%s- %d excessive \'}\' brackets\n",
                        SPACES_FOR_A_TAB,
                        excess_closing_curly_brackets
                );
        }
        if (square_brackets_equality > 0) {
                printf(
                        "%s- %d excessive \'[\' brackets\n",
                        SPACES_FOR_A_TAB,
                        square_brackets_equality
                );
        }
        if (excess_closing_square_brackets > 0) {
                printf(
                        "%s- %d excessive \']\' brackets\n",
                        SPACES_FOR_A_TAB,
                        excess_closing_square_brackets
                );
        }
        if (angle_brackets_equality > 0) {
                printf(
                        "%s- %d excessive \'<\' brackets\n",
                        SPACES_FOR_A_TAB,
                        angle_brackets_equality
                );
        }
        if (excess_closing_angle_brackets > 0) {
                printf(
                        "%s- %d excessive \'>\' brackets\n",
                        SPACES_FOR_A_TAB,
                        excess_closing_angle_brackets
                );
        }
        if (in_double_quotes == TRUE)
                printf("%s- one extra double quote\n", SPACES_FOR_A_TAB);
        if (in_single_quotes == TRUE)
                printf("%s- one extra single quote\n", SPACES_FOR_A_TAB);
        if (invalid_escape_sequences_length > 0)
                printf("%s- invalid space squences:", SPACES_FOR_A_TAB);
        for (int i = 0; i < invalid_escape_sequences_length; i++)
                printf(" \'\\%c\'", invalid_escape_sequences[i]);
        if (invalid_escape_sequences_length > 0) putchar('\n');
        return 0;
}
