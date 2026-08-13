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

void test_parse_term_returns_binary_expr() {
    const std::string source = "2 * 3";

    std::vector<rune::Token> tokens;
    rune::Lexer lexer(source);
    lexer.lex_all(tokens);

    rune::Parser parser(tokens);

    auto binary_expr = parser.parse_term();

    auto *root =
        dynamic_cast<rune::BinaryExpr*>(binary_expr.get());

    assert(root != nullptr);

    auto *left =
        dynamic_cast<const rune::IntegerExpr*>(&root->left());

    auto *right =
        dynamic_cast<const rune::IntegerExpr*>(&root->right());

    assert(left != nullptr);
    assert(right != nullptr);

    assert(left->value() == 2);
    assert(right->value() == 3);

    assert(root->op().kind == rune::TokenKind::TOK_STAR);

    std::cout
        << "test_parse_term_returns_binary_expr PASSED\n";
}

void test_left_associativity() {
    const std::string source = "8 / 2 * 3";

    std::vector<rune::Token> tokens;
    rune::Lexer lexer(source);
    lexer.lex_all(tokens);

    rune::Parser parser(tokens);

    auto binary_expr = parser.parse_term();

    auto *root =
        dynamic_cast<rune::BinaryExpr*>(binary_expr.get());

    assert(root != nullptr);

    auto *left =
        dynamic_cast<const rune::BinaryExpr*>(&root->left());

    auto *right =
        dynamic_cast<const rune::IntegerExpr*>(&root->right());

    assert(root->op().kind == rune::TokenKind::TOK_STAR);

    assert(left != nullptr);

    assert(right != nullptr);
    assert(right->value() == 3);

    assert(left->op().kind == rune::TokenKind::TOK_SLASH);

    auto *left_grandchild =
        dynamic_cast<const rune::IntegerExpr*>(&left->left());
    
    auto *right_grandchild =
        dynamic_cast<const rune::IntegerExpr*>(&left->right());

    assert(left_grandchild != nullptr);
    assert(right_grandchild != nullptr);

    assert(left_grandchild->value() == 8);
    assert(right_grandchild->value() == 2);

    std::cout
        << "test_left_associativity PASSED\n";
}

void run_tests() {
    test_parse_factor_returns_integer_expr();
    test_parse_term_returns_binary_expr();
    test_left_associativity();
} 
