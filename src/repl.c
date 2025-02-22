#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "strings.h"
#include "token.h"

int main() {
    char line[256];
    char literal[256];

    printf("Hello, this is the monkey programming language!\n");
    printf("Feel free to type any commands\n");

    // Print prompt
    printf(">> ");

    // Use fgets instead of scanf to read entire lines
    while (fgets(line, sizeof(line), stdin) != NULL) {
        int len = (int) strlen(line);

        // Remove trailing newline if present
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
            len--;
        }

        if (len == 0) {
            printf(">> ");
            continue;
        }

        lexer_t lexer = lexer_new(line, len);

        while (1) {
            token_t token = lexer_next_token(&lexer);
            const char *token_type_str = token_type_to_string(token.type);
            string_to_c_string_copy(literal, token.literal, 256);
            printf("type=%s | literal=%s\n", token_type_str, literal);
            if (token.type == TOKEN_EOF) {
                break;
            }
        }

        // Print prompt for next line
        printf(">> ");
    }

    printf("\nGoodbye!\n");
    return 0;
}
