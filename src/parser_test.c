#include "parser.h"
#include <stdlib.h>
#include <string.h>
#include "../lib/unity.h"
#include "ast.h"
#include "lexer.h"
#include "strings.h"

void setUp() {}
void tearDown(){};

struct test_t {
    string_t expected_identifier;
};

void check_parser_errors(parser_t *parser) {
    if (parser->errors.length > 0) {
        char *message = malloc(sizeof(char) * 256);
        char *error_message = malloc(sizeof(char) * 256);
        snprintf(error_message, 256, "parser has %lu errors\n", parser->errors.length);
        TEST_MESSAGE(error_message);

        for (size_t i = 0; i < parser->errors.length; i++) {
            string_to_c_string_copy(message, &parser->errors.head[i], 256);
            snprintf(error_message, 256, "%s\n", message);
            TEST_MESSAGE(error_message);
        }

        free(message);
        TEST_FAIL();
    }
}

void test_let_statements() {
    char *input = "let x = 5;\n"
                  "let y = 10;\n"
                  "let foobar = 838383;\n";

    lexer_t lexer = lexer_new(input, strlen(input));
    parser_t parser = parser_new(&lexer);
    program_t *program = parser_parse_program(&parser);
    check_parser_errors(&parser);


    TEST_ASSERT_NOT_NULL(program);

    TEST_ASSERT_EQUAL(3, program->length);

    struct test_t tests[3] = {
            {string_new_from_literal("x")},
            {string_new_from_literal("y")},
            {string_new_from_literal("foobar")},
    };

    for (int i = 0; i < 3; i++) {
        statement_t statement = program->statements[i];
        struct test_t test = tests[i];

        TEST_ASSERT_EQUAL(LET_STATEMENT, statement.type);


        string_t let_str = string_new_from_literal("let");
        string_t *literal = let_statement_token_literal(&statement.let_stmt);

        TEST_ASSERT_TRUE(string_equals(&let_str, literal));

        TEST_ASSERT_TRUE(string_equals(&test.expected_identifier, statement.let_stmt.name.value));

        string_t *name_literal = identifier_expression_token_literal(&statement.let_stmt.name);

        TEST_ASSERT_TRUE(string_equals(&test.expected_identifier, name_literal));
    }

    parser_free(&parser);
}

void test_return_statements() {
    char *input = "return 5;\n"
                  "return 10;\n"
                  "return 993322;\n";

    lexer_t lexer = lexer_new(input, strlen(input));
    parser_t parser = parser_new(&lexer);
    program_t *program = parser_parse_program(&parser);
    check_parser_errors(&parser);


    TEST_ASSERT_NOT_NULL(program);

    TEST_ASSERT_EQUAL(3, program->length);

    string_t return_str = string_new_from_literal("return");

    for (size_t i = 0; i < program->length; i++) {
        statement_t statement = program->statements[i];
        TEST_ASSERT_EQUAL(RETURN_STATEMENT, statement.type);

        string_t *literal = return_statement_token_literal(&statement.return_stmt);
        TEST_ASSERT_TRUE(string_equals(&return_str, literal));
    }
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_let_statements);
    RUN_TEST(test_return_statements);
    return UNITY_END();
}
