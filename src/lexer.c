#include "lexer.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "strings.h"
#include "token.h"

void read_char(lexer_t *lexer) {
    if (lexer->read_position >= lexer->input_size) {
        lexer->ch = 0;
    } else {
        lexer->ch = lexer->input->data[lexer->read_position];
    }

    lexer->position = lexer->read_position;
    lexer->read_position += 1;
}

lexer_t lexer_new(char *input, size_t input_size) {
    string_t *data = malloc(sizeof(string_t));
    *data = string_new_from_literal(input);
    lexer_t l = {data, input_size, 0, 0, 0};
    read_char(&l);
    return l;
}

bool is_letter(char ch) { return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') || ch == '_'; }

bool is_digit(char ch) { return '0' <= ch && ch <= '9'; }

string_t *read_number(lexer_t *lexer) {
    int position = lexer->position;
    while (is_digit(lexer->ch)) {
        read_char(lexer);
    }

    int len = lexer->position - position;
    return string_slice(position, len, lexer->input);
}

string_t *read_idetifier(lexer_t *lexer) {
    int position = lexer->position;
    while (is_letter(lexer->ch)) {
        read_char(lexer);
    }

    int len = lexer->position - position;
    return string_slice(position, len, lexer->input);
}

token_types lookup_ident(string_t *ident) {
    string_t fn_str = string_new_from_literal("fn");
    string_t let_str = string_new_from_literal("let");
    string_t true_str = string_new_from_literal("true");
    string_t false_str = string_new_from_literal("false");
    string_t if_str = string_new_from_literal("if");
    string_t else_str = string_new_from_literal("else");
    string_t return_str = string_new_from_literal("return");

    if (string_equals(ident, &fn_str)) {
        return FUNCTION;
    }

    if (string_equals(ident, &let_str)) {
        return LET;
    }

    if (string_equals(ident, &true_str)) {
        return TRUE;
    }

    if (string_equals(ident, &false_str)) {
        return FALSE;
    }

    if (string_equals(ident, &if_str)) {
        return IF;
    }

    if (string_equals(ident, &else_str)) {
        return ELSE;
    }

    if (string_equals(ident, &return_str)) {
        return RETURN;
    }

    return IDENT;
}

void skip_whitespace(lexer_t *lexer) {
    while (lexer->ch == ' ' || lexer->ch == '\t' || lexer->ch == '\n' || lexer->ch == '\r') {
        read_char(lexer);
    }
}

char peek_char(lexer_t *lexr) {
    if ((unsigned int) lexr->read_position >= lexr->input->length) {
        return 0;
    }

    return lexr->input->data[lexr->read_position];
}

token_t lexer_next_token(lexer_t *lexer) {
    token_t token = {};
    skip_whitespace(lexer);

    switch (lexer->ch) {
        case '=':
            if (peek_char(lexer) == '=') {
                unsigned int initial_pos = lexer->position;
                read_char(lexer);
                token.type = EQ;
                token.literal = string_slice(initial_pos, 2, lexer->input);
            } else {
                token.type = ASSIGN;
                token.literal = string_slice(lexer->position, 1, lexer->input);
            }
            break;

        case '+':
            token.type = PLUS;
            token.literal = string_slice(lexer->position, 1, lexer->input);
            break;

        case '-':
            token.type = MINUS;
            token.literal = string_slice(lexer->position, 1, lexer->input);
            break;

        case '!':
            if (peek_char(lexer) == '=') {
                unsigned int initial_pos = lexer->position;
                read_char(lexer);
                token.type = NOT_EQ;
                token.literal = string_slice(initial_pos, 2, lexer->input);
            } else {
                token.type = BANG;
                token.literal = string_slice(lexer->position, 1, lexer->input);
            }
            break;

        case '/':
            token.type = SLASH;
            token.literal = string_slice(lexer->position, 1, lexer->input);
            break;

        case '*':
            token.type = ASTERISK;
            token.literal = string_slice(lexer->position, 1, lexer->input);
            break;

        case '<':
            token.type = LT;
            token.literal = string_slice(lexer->position, 1, lexer->input);
            break;

        case '>':
            token.type = GT;
            token.literal = string_slice(lexer->position, 1, lexer->input);
            break;

        case ';':
            token.type = SEMICOLON;
            token.literal = string_slice(lexer->position, 1, lexer->input);
            break;

        case '(':
            token.type = LPAREN;
            token.literal = string_slice(lexer->position, 1, lexer->input);
            break;

        case ')':
            token.type = RPAREN;
            token.literal = string_slice(lexer->position, 1, lexer->input);
            break;

        case ',':
            token.type = COMMA;
            token.literal = string_slice(lexer->position, 1, lexer->input);
            break;

        case '{':
            token.type = LBRACE;
            token.literal = string_slice(lexer->position, 1, lexer->input);
            break;

        case '}':
            token.type = RBRACE;
            token.literal = string_slice(lexer->position, 1, lexer->input);
            break;

        case 0:
            token.type = TOKEN_EOF;
            token.literal = string_slice(0, 0, lexer->input);
            break;

        default: // Handle default case or errors
            if (is_letter(lexer->ch)) {
                token.literal = read_idetifier(lexer);
                token.type = lookup_ident(token.literal);
                return token;
            }

            if (is_digit(lexer->ch)) {
                token.literal = read_number(lexer);
                token.type = INT;
                return token;
            }

            token.type = ILLEGAL;
            strncpy(token.literal->data, &lexer->ch, 1);
            token.literal->data[1] = '\0';

            break;
    }

    read_char(lexer);
    return token;
}
