.PHONY: all lexer_tests parser_tests interpreter_tests test clean s

CXX = g++
CXXFLAGS = -std=c++20 -Iinclude -Werror -Wall -Wpedantic -Wextra -fsanitize=address,undefined -g

BUILD_DIR = build/

PROD_SRC = src/main.cpp                            \
		   src/lexer.cpp                           \
		   src/token.cpp                           \
		   src/parser.cpp                          \
		   src/interpreter.cpp                     \
		   src/ast.cpp                             \
		   src/file_utils.cpp

PROD_OUT = $(BUILD_DIR)runec

LEXER_TEST_SRC = src/lexer.cpp                     \
				 src/token.cpp                     \
				 tests/lexer_tests.cpp

LEXER_TEST_OUT = $(BUILD_DIR)runec_lexer_tests

PARSER_TEST_SRC = src/lexer.cpp                    \
				  src/ast.cpp                      \
				  src/token.cpp                    \
				  src/parser.cpp                   \
				  tests/parser_tests.cpp

PARSER_TEST_OUT = $(BUILD_DIR)runec_parser_tests

INTERPRETER_TEST_SRC = src/ast.cpp                 \
					   src/interpreter.cpp         \
					   tests/interpreter_tests.cpp 

INTERPRETER_TEST_OUT = $(BUILD_DIR)runec_interpreter_tests

TEST_OUT = $(LEXER_TEST_OUT) $(PARSER_TEST_OUT) $(INTERPRETER_TEST_OUT)

all: $(PROD_SRC)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(PROD_SRC) -o $(PROD_OUT)

lexer_tests: $(LEXER_TEST_SRC)
	@mkdir -p $(BUILD_DIR)
	@$(CXX) $(CXXFLAGS) $(LEXER_TEST_SRC) -o $(LEXER_TEST_OUT)
	./$(LEXER_TEST_OUT)

parser_tests: $(PARSER_TEST_SRC)
	@mkdir -p $(BUILD_DIR)
	@$(CXX) $(CXXFLAGS) $(PARSER_TEST_SRC) -o $(PARSER_TEST_OUT)
	./$(PARSER_TEST_OUT)

interpreter_tests: $(INTERPRETER_TEST_SRC)
	@mkdir -p $(BUILD_DIR)
	@$(CXX) $(CXXFLAGS) $(INTERPRETER_TEST_SRC) -o $(INTERPRETER_TEST_OUT)
	./$(INTERPRETER_TEST_OUT)

test: parser_tests lexer_tests interpreter_tests

clean:
	rm -f $(PROD_OUT) $(TEST_OUT)

s: clean test all
