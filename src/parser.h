#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "lexer.h"
#include "token.h"


typedef struct {
    lexer_t *lexer;

    struct {
        string_t *head;
        size_t length;
        size_t capacity;
    } errors;

    token_t current_token;
    token_t peek_token;
} parser_t;

parser_t parser_new(lexer_t *lexer);
program_t *parser_parse_program(parser_t *parser);

void parser_append_error(parser_t *parser, string_t str);
void parser_free(parser_t *parser);

#endif
