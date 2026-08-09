#include "rune/lexer.hpp"
#include "rune/token.hpp"
#include "rune/parser.hpp"
#include <iostream>
#include <cassert>
#include <vector>

void run_tests();

int main() {
    run_tests();
}

void test_parse_factor_returns_integer_expr() {
    const std::string source = "42";

    std::vector<rune::Token> tokens;
    rune::Lexer lexer(source);
    lexer.lex_all(tokens);

    rune::Parser parser(tokens);
    
    auto integer_expr = parser.parse_factor();
    auto *integer = dynamic_cast<rune::IntegerExpr*>(integer_expr.get());

    assert(integer != nullptr);
    assert(integer->value() == 42);

    std::cout
        << "test_parse_factor_returns_integer_expr PASSED\n";
}

void run_tests() {
    test_parse_factor_returns_integer_expr();
} 
