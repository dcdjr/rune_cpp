#include "rune/lexer.hpp"
#include "rune/token.hpp"
#include <string>
#include <cassert>
#include <iostream>

void run_tests();
void test_identifier();
void test_keywords();
void test_operators_and_punctuation();

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

void test_comments() {
    const std::string source = "let x = 123;\n// skip all this\nlet y = 456;";
    rune::Lexer lexer(source);

    std::vector<rune::Token> tokens;
    lexer.lex_all(tokens);

    assert(tokens[0].kind == rune::TokenKind::TOK_LET);
    assert(tokens[0].lexeme == "let");

    assert(tokens[1].kind == rune::TokenKind::TOK_IDENTIFIER);
    assert(tokens[1].lexeme == "x");

    assert(tokens[2].kind == rune::TokenKind::TOK_EQUAL);
    assert(tokens[2].lexeme == "=");
    
    assert(tokens[3].kind == rune::TokenKind::TOK_INT);
    assert(tokens[3].lexeme == "123");

    assert(tokens[4].kind == rune::TokenKind::TOK_SEMICOLON);
    assert(tokens[4].lexeme == ";");

    assert(tokens[5].kind == rune::TokenKind::TOK_LET);
    assert(tokens[5].lexeme == "let");

    assert(tokens[6].kind == rune::TokenKind::TOK_IDENTIFIER);
    assert(tokens[6].lexeme == "y");
    
    assert(tokens[7].kind == rune::TokenKind::TOK_EQUAL);
    assert(tokens[7].lexeme == "=");

    assert(tokens[8].kind == rune::TokenKind::TOK_INT);
    assert(tokens[8].lexeme == "456");

    assert(tokens[9].kind == rune::TokenKind::TOK_SEMICOLON);
    assert(tokens[9].lexeme == ";");

    std::cout << "test_comments PASSED\n";
}

void test_operators_and_punctuation() {
    const std::string source = "+ - / * ( ) = ;";
    rune::Lexer lexer(source);

    std::vector<rune::Token> tokens;
    lexer.lex_all(tokens);

    assert(tokens[0].kind == rune::TokenKind::TOK_PLUS);
    assert(tokens[0].lexeme == "+");

    assert(tokens[1].kind == rune::TokenKind::TOK_MINUS);
    assert(tokens[1].lexeme == "-");

    assert(tokens[2].kind == rune::TokenKind::TOK_SLASH);
    assert(tokens[2].lexeme == "/");

    assert(tokens[3].kind == rune::TokenKind::TOK_STAR);
    assert(tokens[3].lexeme == "*");

    assert(tokens[4].kind == rune::TokenKind::TOK_LPAREN);
    assert(tokens[4].lexeme == "(");

    assert(tokens[5].kind == rune::TokenKind::TOK_RPAREN);
    assert(tokens[5].lexeme == ")");

    assert(tokens[6].kind == rune::TokenKind::TOK_EQUAL);
    assert(tokens[6].lexeme == "=");

    assert(tokens[7].kind == rune::TokenKind::TOK_SEMICOLON);
    assert(tokens[7].lexeme == ";");

    std::cout << "test_operators_and_punctuation PASSED\n";
}

void test_line_and_column_tracking() {
    //                          1,5,9,11,13: 1
    //                          1,7,10: 2
    //                          -   -   - - -  -     -  -
    const std::string source = "let age = 13;\nprint age;";
    rune::Lexer lexer(source);

    std::vector<rune::Token> tokens;
    lexer.lex_all(tokens);

    assert(tokens[0].line == 1);
    assert(tokens[0].column == 1);

    assert(tokens[1].line == 1);
    assert(tokens[1].column == 5);

    assert(tokens[2].line == 1);
    assert(tokens[2].column == 9);

    assert(tokens[3].line == 1);
    assert(tokens[3].column == 11);

    assert(tokens[4].line == 1);
    assert(tokens[4].column == 13);

    assert(tokens[5].line == 2);
    assert(tokens[5].column == 1);

    assert(tokens[6].line == 2);
    assert(tokens[6].column == 7);

    assert(tokens[7].line == 2);
    assert(tokens[7].column == 10);

    std::cout
        << "test_line_and_column_tracking PASSED\n";
}

void test_unknown_characters_produce_error() {
    const std::string source = ": \\ | `";
    rune::Lexer lexer(source);

    std::vector<rune::Token> tokens;
    lexer.lex_all(tokens);

    assert(tokens[0].kind == rune::TokenKind::TOK_ERROR);

    assert(tokens[1].kind == rune::TokenKind::TOK_ERROR);

    assert(tokens[2].kind == rune::TokenKind::TOK_ERROR);

    assert(tokens[3].kind == rune::TokenKind::TOK_ERROR);

    std::cout
        << "test_unknown_characters_produce_error PASSED\n";
}

void test_empty_source_produces_only_eof() {
    const std::string source = "";
    rune::Lexer lexer(source);

    std::vector<rune::Token> tokens;
    lexer.lex_all(tokens);

    assert(tokens.size() == 1);
    assert(tokens[0].kind == rune::TokenKind::TOK_EOF);

     std::cout
        << "test_empty_source_produces_only_eof PASSED\n";
}

void run_tests() {
    test_identifier();
    test_keywords();
    test_integers();
    test_comments();
    test_operators_and_punctuation();
    test_line_and_column_tracking();
    test_unknown_characters_produce_error();
    test_empty_source_produces_only_eof();
}
