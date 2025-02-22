#include "parser.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "lexer.h"
#include "strings.h"
#include "token.h"

void next_token(parser_t *parser) {
    parser->current_token = parser->peek_token;
    parser->peek_token = lexer_next_token(parser->lexer);
}

parser_t parser_new(lexer_t *lexer) {
    parser_t parser = {.lexer = lexer};
    parser.errors.length = 0;
    parser.errors.capacity = 20;
    parser.errors.head = malloc(sizeof(string_t) * parser.errors.capacity);

    next_token(&parser);
    next_token(&parser);

    return parser;
}

bool curr_token_is(parser_t *parser, token_types t) { return parser->current_token.type == t; }

bool peek_token_is(parser_t *parser, token_types t) { return parser->peek_token.type == t; }

void peek_error(parser_t *parser, token_types t) {
    string_t error = string_new(malloc(sizeof(char) * 256), 256);
    const char *expected = token_type_to_string(t);
    const char *actual = token_type_to_string(parser->peek_token.type);

    snprintf(error.data, error.length, "expected next token to be %s, got %s instead", expected, actual);
    parser_append_error(parser, error);
}

bool expect_peek(parser_t *parser, token_types t) {
    if (peek_token_is(parser, t)) {
        next_token(parser);
        return true;
    }

    peek_error(parser, t);
    return false;
}


bool parse_let_statement(let_statement_t *dest, parser_t *parser) {
    dest->token.type = parser->current_token.type;
    dest->token.literal = parser->current_token.literal;

    if (!expect_peek(parser, IDENT)) {
        return false;
    }

    dest->name.token = parser->current_token;
    dest->name.value = parser->current_token.literal;

    if (!expect_peek(parser, ASSIGN)) {
        return false;
    }

    // TODO: We are skipping the expressions until we encounter a semicolon
    while (!curr_token_is(parser, SEMICOLON)) {
        next_token(parser);
    }

    return true;
}

bool parse_return_statement(return_statement_t *dest, parser_t *parser) {
    dest->token.type = parser->current_token.type;
    dest->token.literal = parser->current_token.literal;

    next_token(parser);

    // TODO: we're skipping the expressions until we encounter a semicolon
    while (!curr_token_is(parser, SEMICOLON)) {
        next_token(parser);
    }

    return true;
}


bool parse_statement(statement_t *dest, parser_t *parser) {

    switch (parser->current_token.type) {
        case LET:
            dest->type = LET_STATEMENT;
            return parse_let_statement(&dest->let_stmt, parser);

        case RETURN:
            dest->type = RETURN_STATEMENT;
            return parse_return_statement(&dest->return_stmt, parser);

        default:
            return false;
    }
}

program_t *parser_parse_program(parser_t *parser) {
    program_t *program = program_new();

    while (parser->current_token.type != TOKEN_EOF) {
        statement_t stmt;
        bool parsed_successfully = parse_statement(&stmt, parser);
        if (parsed_successfully) {
            program_append(program, stmt);
        }

        next_token(parser);
    }

    return program;
}

void parser_append_error(parser_t *parser, string_t str) {
    if (parser->errors.length == parser->errors.capacity) {
        // We need to re-allocate
        string_t *new_head = malloc(sizeof(string_t) * parser->errors.capacity * 2);
        memcpy(new_head, parser->errors.head, (sizeof(string_t)) * parser->errors.length);
        free(parser->errors.head);
        parser->errors.head = new_head;
    }

    parser->errors.head[parser->errors.length] = str;
    parser->errors.length++;
}

void parser_free(parser_t *parser) { free(parser->errors.head); }
