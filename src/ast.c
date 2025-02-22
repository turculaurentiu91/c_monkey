
#include <stdlib.h>
#include <string.h>

#include "ast.h"


string_t *let_statement_token_literal(let_statement_t *let) { return let->token.literal; }
string_t *return_statement_token_literal(return_statement_t *return_stmt) { return return_stmt->token.literal; }

string_t *identifier_expression_token_literal(identifier_expression_t *identifier) { return identifier->token.literal; }

program_t *program_new() {
    program_t *program = malloc(sizeof(program_t));

    program->length = 0;
    program->capacity = 100;
    program->statements = malloc(sizeof(statement_t) * program->capacity);

    return program;
}

void program_free(program_t *program) {
    free(program->statements);
    free(program);
}

void program_append(program_t *program, statement_t s) {
    if (program->length == program->capacity) {
        // We need to re-allocate
        statement_t *new_head = malloc(sizeof(statement_t) * program->capacity * 2);
        memcpy(new_head, program->statements, (sizeof(statement_t)) * program->length);
        free(program->statements);
        program->statements = new_head;
    }

    program->statements[program->length] = s;
    program->length++;
}
