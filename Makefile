# Define directories
BUILD_DIR = build
LIB_DIR = lib
SRC_DIR = src
TESTS_DIR = $(BUILD_DIR)/tests

# Define source files
UNITY_C = $(LIB_DIR)/unity.c
LEXER_C = $(SRC_DIR)/lexer.c
AST_C = $(SRC_DIR)/ast.c
PARSER_C = $(SRC_DIR)/parser.c
STRINGS_C = $(SRC_DIR)/strings.c
TOKEN_C = $(SRC_DIR)/token.c
REPL_C = $(SRC_DIR)/repl.c
LEXER_TEST_C = $(SRC_DIR)/lexer_test.c
STRINGS_TEST_C = $(SRC_DIR)/strings_test.c
PARSER_TEST_C = $(SRC_DIR)/parser_test.c

# Define object files
UNITY_OBJ = $(BUILD_DIR)/unity.o
LEXER_OBJ = $(BUILD_DIR)/lexer.o
AST_OBJ = $(BUILD_DIR)/ast.o
PARSER_OBJ = $(BUILD_DIR)/parser.o
TOKEN_OBJ = $(BUILD_DIR)/token.o
LEXER_TEST_OBJ = $(TESTS_DIR)/lexer_test.o
REPL_OBJ = $(BUILD_DIR)/repl.o
STRINGS_TEST_OBJ = $(TESTS_DIR)/strings_test.o
STRINGS_OBJ = $(BUILD_DIR)/strings.o
PARSER_TEST_OBJ = $(BUILD_DIR)/parser_test.o

# Define executables
LEXER_TEST = $(TESTS_DIR)/lexer_test
PARSER_TEST = $(TESTS_DIR)/parser_test
STRINGS_TEST = $(TESTS_DIR)/strings
REP = $(BUILD_DIR)/repl

# Compiler flags (adjust as needed)
CFLAGS = -Wall -Wextra -g  # Add -g for debugging

# Default target
all: $(LEXER_TEST) $(STRINGS_TEST) $(PARSER_TEST) $(REP)

# Rule for building the lexer_test executable
$(LEXER_TEST): $(LEXER_TEST_OBJ) $(UNITY_OBJ) $(LEXER_OBJ) $(STRINGS_OBJ)
	$(CC) $(CFLAGS) $(LEXER_TEST_OBJ) $(UNITY_OBJ) $(LEXER_OBJ) $(STRINGS_OBJ) -o $(LEXER_TEST)

$(PARSER_TEST): $(PARSER_TEST_OBJ) $(UNITY_OBJ) $(LEXER_OBJ) $(STRINGS_OBJ) $(PARSER_OBJ) $(AST_OBJ) $(TOKEN_OBJ)
	$(CC) $(CFLAGS) $(PARSER_TEST_OBJ) $(AST_OBJ) $(LEXER_OBJ) $(UNITY_OBJ) $(PARSER_OBJ) $(TOKEN_OBJ) $(STRINGS_OBJ) -o $(PARSER_TEST)

$(STRINGS_TEST): $(STRINGS_TEST_OBJ) $(STRINGS_OBJ) $(UNITY_OBJ) 
	$(CC) $(CFLAGS) $(STRINGS_TEST_OBJ) $(STRINGS_OBJ) $(UNITY_OBJ) -o $(STRINGS_TEST)

$(REP): $(REPL_OBJ) $(LEXER_OBJ) $(STRINGS_OBJ) $(TOKEN_OBJ)
	$(CC) $(CFLAGS) $(REPL_OBJ) $(LEXER_OBJ) $(STRINGS_OBJ) $(TOKEN_OBJ) -o $(REP)

# Rule for building the lexer_test object file
$(LEXER_TEST_OBJ): $(LEXER_TEST_C) $(SRC_DIR)/lexer.h $(SRC_DIR)/token.h $(LIB_DIR)/unity.h # Add token.h dependency
	$(CC) $(CFLAGS) -c $(LEXER_TEST_C) -o $(LEXER_TEST_OBJ)

$(PARSER_TEST_OBJ): $(PARSER_TEST_C) $(SRC_DIR)/lexer.h $(SRC_DIR)/token.h $(SRC_DIR)/ast.h $(SRC_DIR)/parser.h $(LIB_DIR)/unity.h # Add token.h dependency
	$(CC) $(CFLAGS) -c $(PARSER_TEST_C) -o $(PARSER_TEST_OBJ)

$(STRINGS_TEST_OBJ): $(STRINGS_C) $(SRC_DIR)/strings.h
	$(CC) $(CFLAGS) -c $(STRINGS_TEST_C) -o $(STRINGS_TEST_OBJ)

# Rule for building the unity object file
$(UNITY_OBJ): $(UNITY_C) $(LIB_DIR)/unity.h $(LIB_DIR)/unity_internals.h # Add unity headers
	$(CC) $(CFLAGS) -c $(UNITY_C) -o $(UNITY_OBJ)

$(LEXER_OBJ): $(LEXER_C) $(SRC_DIR)/lexer.h $(SRC_DIR)/token.h
	$(CC) $(CFLAGS) -c $(LEXER_C) -o $(LEXER_OBJ)

$(PARSER_OBJ): $(PARSER_C) $(SRC_DIR)/parser.h $(SRC_DIR)/token.h
	$(CC) $(CFLAGS) -c $(PARSER_C) -o $(PARSER_OBJ)

$(AST_OBJ): $(AST_C) $(SRC_DIR)/ast.h $(SRC_DIR)/token.h
	$(CC) $(CFLAGS) -c $(AST_C) -o $(AST_OBJ)

$(STRINGS_OBJ): $(STRINGS_C) $(SRC_DIR)/strings.h
	$(CC) $(CFLAGS) -c $(STRINGS_C) -o $(STRINGS_OBJ)

$(TOKEN_OBJ): $(SRC_DIR)/token.h $(SRC_DIR)/strings.h
	$(CC) $(CFLAGS) -c $(TOKEN_C) -o $(TOKEN_OBJ)

$(REPL_OBJ): $(REPL_C) $(SRC_DIR)/lexer.h $(SRC_DIR)/token.h $(SRC_DIR)/strings.h
	$(CC) $(CFLAGS) -c $(REPL_C) -o $(REPL_OBJ) 

lexer_test: $(LEXER_TEST)
	./$(LEXER_TEST)

parser_test: $(PARSER_TEST)
	./$(PARSER_TEST)

strings_test: $(STRINGS_TEST) $(STRINGS_TEST_OBJ) $(STRINGS_OBJ) $(STRINGS_C) $(STRINGS_TEST_C) $(SRC_DIR)/strings.h
	./$(STRINGS_TEST)

repl: $(REP)
	./$(REP)

# Clean target
clean:
	find $(BUILD_DIR) -type f -exec rm {} +

# Phony targets (for clarity)
.PHONY: all clean
