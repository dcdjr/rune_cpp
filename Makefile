.PHONY: all test clean

CXX = g++
CXXFLAGS = -std=c++20 -Iinclude -Werror -Wall -Wpedantic -Wextra -fsanitize=address,undefined -g

PROD_SRC = src/main.cpp       \
		   src/lexer.cpp      \
		   src/token.cpp      \
		   src/parser.cpp     \
		   src/file_utils.cpp

PROD_OUT = runec

TEST_SRC = src/lexer.cpp          \
		   src/token.cpp          \
		   src/parser.cpp         \
		   tests/lexer_tests.cpp  \
		   tests/parser_tests.cpp \

TEST_OUT = runec_tests

all: $(PROD_SRC)
	$(CXX) $(CXXFLAGS) $(PROD_SRC) -o $(PROD_OUT)

test: $(TEST_SRC)
	$(CXX) $(CXXFLAGS) $(TEST_SRC) -o $(TEST_OUT)
	./$(TEST_OUT)

clean:
	rm -f $(PROD_OUT) $(TEST_OUT)
