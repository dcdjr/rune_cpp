#include "rune/lexer.hpp"
#include "rune/token.hpp"
#include <string>
#include <cassert>
#include <iostream>

void run_tests();
void test_identifier();
void test_keywords();

int main() {
    run_tests();
}

void test_identifier() {
    const std::string source = "hello world2 _value";
    rune::Lexer lexer(source);

    std::vector<rune::Token> tokens;
    lexer.lex_all(tokens);

    assert(tokens[0].kind == rune::TokenKind::TOK_IDENTIFIER);
    assert(tokens[0].lexeme == "hello");

    assert(tokens[1].kind == rune::TokenKind::TOK_IDENTIFIER);
    assert(tokens[1].lexeme == "world2");

    assert(tokens[2].kind == rune::TokenKind::TOK_IDENTIFIER);
    assert(tokens[2].lexeme == "_value");

    std::cout << "test_identifier PASSED\n";
}

void test_keywords() {
    const std::string source = "let print not_keyword";
    rune::Lexer lexer(source);

    std::vector<rune::Token> tokens;
    lexer.lex_all(tokens);

    assert(tokens[0].kind == rune::TokenKind::TOK_LET);
    assert(tokens[0].lexeme == "let");

    assert(tokens[1].kind == rune::TokenKind::TOK_PRINT);
    assert(tokens[1].lexeme == "print");

    assert(tokens[2].kind == rune::TokenKind::TOK_IDENTIFIER);
    assert(tokens[2].lexeme == "not_keyword");

    std::cout << "test_keywords PASSED\n";
}

void test_integers() {
    const std::string source = "1 432 943 not_integer";
    rune::Lexer lexer(source);

    std::vector<rune::Token> tokens;
    lexer.lex_all(tokens);

    assert(tokens[0].kind == rune::TokenKind::TOK_INT);
    assert(tokens[0].lexeme == "1");

    assert(tokens[1].kind == rune::TokenKind::TOK_INT);
    assert(tokens[1].lexeme == "432");

    assert(tokens[2].kind == rune::TokenKind::TOK_INT);
    assert(tokens[2].lexeme == "943");
    
    assert(tokens[3].kind == rune::TokenKind::TOK_IDENTIFIER);
    assert(tokens[3].lexeme == "not_integer");

    std::cout << "test_integers PASSED\n";
}

void run_tests() {
    test_identifier();
    test_keywords();
    test_integers();
}
