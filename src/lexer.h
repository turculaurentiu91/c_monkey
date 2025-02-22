//
// Created by Laurentiu Turcu on 05/02/25.
//

#include <stddef.h>
#include "token.h"

#ifndef LEXER_H
#define LEXER_H

// Lexer structure definition
typedef struct {
    string_t *input;
    int input_size;
    int position;
    int read_position;
    char ch;
} lexer_t;

// Core lexer functions
lexer_t lexer_new(char *input, size_t input_size);
token_t lexer_next_token(lexer_t *l);

#endif // LEXER_H
