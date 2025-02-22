//
// Created by Laurentiu Turcu on 05/02/25.
//

#ifndef TOKEN_H
#define TOKEN_H

#include "strings.h"

#define MAX_TOKEN_LITERAL_SIZE 64 // Define a maximum size

typedef enum {
    ILLEGAL,
    TOKEN_EOF,

    IDENT,
    INT,

    ASSIGN,
    PLUS,
    MINUS,
    BANG,
    ASTERISK,
    SLASH,
    EQ,
    NOT_EQ,

    LT,
    GT,

    COMMA,
    SEMICOLON,

    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,

    FUNCTION,
    LET,
    TRUE,
    FALSE,
    IF,
    ELSE,
    RETURN
} token_types;

typedef struct {
    token_types type;
    string_t *literal;
} token_t;

const char *token_type_to_string(token_types type);
#endif
