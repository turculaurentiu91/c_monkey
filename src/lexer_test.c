#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/unity.h"
#include "strings.h"
#include "token.h"

struct test_result {
    token_types expected_type;
    string_t expected_literal;
};

void setUp() {}

void tearDown() {}

void test_lexer() {
    char *input = "let five = 5;\n"
                  "let ten = 10;\n"
                  "\n"
                  "let add = fn(x, y) {\n"
                  "    x + y;\n"
                  "};\n"
                  "let result = add(five, ten);\n"
                  "!-/*5;\n"
                  "5 < 10 > 5;\n"
                  "if (5 < 10) {\n"
                  "    return true;\n"
                  "} else {\n"
                  "    return false;\n"
                  "}\n"
                  "\n"
                  "10 == 10;\n"
                  "10 != 9;\n";

    struct test_result expected_results[] = {
            {LET, string_new_from_literal("let")},     {IDENT, string_new_from_literal("five")},
            {ASSIGN, string_new_from_literal("=")},    {INT, string_new_from_literal("5")},
            {SEMICOLON, string_new_from_literal(";")}, {LET, string_new_from_literal("let")},
            {IDENT, string_new_from_literal("ten")},   {ASSIGN, string_new_from_literal("=")},
            {INT, string_new_from_literal("10")},      {SEMICOLON, string_new_from_literal(";")},
            {LET, string_new_from_literal("let")},     {IDENT, string_new_from_literal("add")},
            {ASSIGN, string_new_from_literal("=")},    {FUNCTION, string_new_from_literal("fn")},
            {LPAREN, string_new_from_literal("(")},    {IDENT, string_new_from_literal("x")},
            {COMMA, string_new_from_literal(",")},     {IDENT, string_new_from_literal("y")},
            {RPAREN, string_new_from_literal(")")},    {LBRACE, string_new_from_literal("{")},
            {IDENT, string_new_from_literal("x")},     {PLUS, string_new_from_literal("+")},
            {IDENT, string_new_from_literal("y")},     {SEMICOLON, string_new_from_literal(";")},
            {RBRACE, string_new_from_literal("}")},    {SEMICOLON, string_new_from_literal(";")},
            {LET, string_new_from_literal("let")},     {IDENT, string_new_from_literal("result")},
            {ASSIGN, string_new_from_literal("=")},    {IDENT, string_new_from_literal("add")},
            {LPAREN, string_new_from_literal("(")},    {IDENT, string_new_from_literal("five")},
            {COMMA, string_new_from_literal(",")},     {IDENT, string_new_from_literal("ten")},
            {RPAREN, string_new_from_literal(")")},    {SEMICOLON, string_new_from_literal(";")},
            {BANG, string_new_from_literal("!")},      {MINUS, string_new_from_literal("-")},
            {SLASH, string_new_from_literal("/")},     {ASTERISK, string_new_from_literal("*")},
            {INT, string_new_from_literal("5")},       {SEMICOLON, string_new_from_literal(";")},
            {INT, string_new_from_literal("5")},       {LT, string_new_from_literal("<")},
            {INT, string_new_from_literal("10")},      {GT, string_new_from_literal(">")},
            {INT, string_new_from_literal("5")},       {SEMICOLON, string_new_from_literal(";")},
            {IF, string_new_from_literal("if")},       {LPAREN, string_new_from_literal("(")},
            {INT, string_new_from_literal("5")},       {LT, string_new_from_literal("<")},
            {INT, string_new_from_literal("10")},      {RPAREN, string_new_from_literal(")")},
            {LBRACE, string_new_from_literal("{")},    {RETURN, string_new_from_literal("return")},
            {TRUE, string_new_from_literal("true")},   {SEMICOLON, string_new_from_literal(";")},
            {RBRACE, string_new_from_literal("}")},    {ELSE, string_new_from_literal("else")},
            {LBRACE, string_new_from_literal("{")},    {RETURN, string_new_from_literal("return")},
            {FALSE, string_new_from_literal("false")}, {SEMICOLON, string_new_from_literal(";")},
            {RBRACE, string_new_from_literal("}")},    {INT, string_new_from_literal("10")},
            {EQ, string_new_from_literal("==")},       {INT, string_new_from_literal("10")},
            {SEMICOLON, string_new_from_literal(";")}, {INT, string_new_from_literal("10")},
            {NOT_EQ, string_new_from_literal("!=")},   {INT, string_new_from_literal("9")},
            {SEMICOLON, string_new_from_literal(";")}, {EOF, string_new_from_literal("")},

    };

    lexer_t lexer = lexer_new(input, strlen(input));

    for (int i = 0; i < 73; i++) {
        token_t token = lexer_next_token(&lexer);
        char *message = malloc(sizeof(char) * 1024);
        sprintf(message,
                "Failed to compare literals | interation %d | token literal pointer %c | lexer position %d | lexer "
                "char %c",
                i, token.literal->data[0], lexer.position, lexer.ch);

        TEST_ASSERT_EQUAL_INT(expected_results[i].expected_type, token.type);
        TEST_ASSERT_TRUE_MESSAGE(string_equals(&expected_results[i].expected_literal, token.literal), message);
    }
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_lexer);
    return UNITY_END();
}
