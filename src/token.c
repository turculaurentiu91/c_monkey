#include "token.h"

const char *token_type_to_string(token_types type) {
    switch (type) {
        case TOKEN_EOF:
            return "EOF";

        case IDENT:
            return "IDENT";

        case INT:
            return "INT";

        case ASSIGN:
            return "=";

        case PLUS:
            return "+";

        case MINUS:
            return "-";

        case BANG:
            return "!";

        case ASTERISK:
            return "*";

        case SLASH:
            return "/";

        case EQ:
            return "==";

        case NOT_EQ:
            return "!=";

        case GT:
            return ">";

        case LT:
            return "<";

        case COMMA:
            return ",";

        case SEMICOLON:
            return ";";

        case LPAREN:
            return "(";

        case RPAREN:
            return ")";

        case LBRACE:
            return "{";

        case RBRACE:
            return "]";

        case FUNCTION:
            return "function";

        case LET:
            return "let";

        case TRUE:
            return "true";

        case FALSE:
            return "false";

        case IF:
            return "if";

        case ELSE:
            return "else";

        case RETURN:
            return "return";

        case ILLEGAL:
            return "ILLEGAL";
    }
}
