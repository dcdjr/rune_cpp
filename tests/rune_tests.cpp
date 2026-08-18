#include "rune/lexer.hpp"
#include "rune/parser.hpp"
#include "rune/interpreter.hpp"
#include <sstream>
#include <iostream>
#include <cassert>
#include <string>

void run_tests();

int main() {
    run_tests();
}

void test_end_to_end_program_1() {
    const std::string source =
        "let x = 5;"
        "x = x * 2;"
        "print x;";
    
    rune::Lexer lexer(source);
    std::vector<rune::Token> tokens;
    lexer.lex_all(tokens);

    rune::Parser parser(tokens);
    auto statements = parser.parse_program();

    std::ostringstream output;
    rune::Interpreter interpreter(output);

    interpreter.interpret(statements);

    assert(output.str() == "10\n");

    std::cout
        << "test_end_to_end_program_1 PASSED\n";
}

void run_tests() {
    test_end_to_end_program_1();
} 
