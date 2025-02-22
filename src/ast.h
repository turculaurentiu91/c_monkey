#ifndef AST_H
#define AST_H

#include <stddef.h>
#include "strings.h"
#include "token.h"

#define PROGRAM_SIZE_CHUNK = 100;

typedef enum {
    LET_STATEMENT,
} statement_types;


typedef enum { IDENTIFIER_EXPRESSION } expression_types;


typedef struct {
    token_t token;
    string_t *value;
} identifier_expression_t;


typedef struct {
    expression_types type;
    union {
        identifier_expression_t identifier;
    };
} expression_t;

typedef struct {
    token_t token;
    identifier_expression_t name;
    expression_t value;
} let_statement_t;


typedef struct {
    statement_types type;
    union {
        let_statement_t let;
    };
} statement_t;

typedef struct {
    statement_t *statements;
    size_t length;
    size_t capacity;
} program_t;

string_t *let_statement_token_literal(let_statement_t *let);
string_t *identifier_expression_token_literal(identifier_expression_t *identifier);

program_t *program_new();
void program_append(program_t *program, statement_t s);
void program_free(program_t *program);

#endif // AST_H
