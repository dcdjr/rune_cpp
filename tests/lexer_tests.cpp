#include "rune/lexer.hpp"
#include "rune/token.hpp"
#include <string>
#include <cassert>
#include <iostream>
#include <vector>
#include <string_view>

void run_tests();
void assert_token(
    const rune::Token& token,
    rune::TokenKind expected_kind,
    std::string_view expected_lexeme
);

int main() {
    run_tests();
}

void assert_token(
    const rune::Token& token,
    rune::TokenKind expected_kind,
    std::string_view expected_lexeme
) {
    assert(token.kind == expected_kind);
    assert(token.lexeme == expected_lexeme);
}

void test_identifier() {
    const std::string source = "hello world2 _value";
    rune::Lexer lexer(source);

    std::vector<rune::Token> tokens;
    lexer.lex_all(tokens);

    assert(tokens.size() == 4);
    assert_token(tokens[0], rune::TokenKind::TOK_IDENTIFIER, "hello");
    assert_token(tokens[1], rune::TokenKind::TOK_IDENTIFIER, "world2");
    assert_token(tokens[2], rune::TokenKind::TOK_IDENTIFIER, "_value");
    assert(tokens.back().kind == rune::TokenKind::TOK_EOF);

    std::cout << "test_identifier PASSED\n";
}

void test_keywords() {
    const std::string source = "let print not_keyword";
    rune::Lexer lexer(source);

    std::vector<rune::Token> tokens;
    lexer.lex_all(tokens);

    assert(tokens.size() == 4);
    assert_token(tokens[0], rune::TokenKind::TOK_LET, "let");
    assert_token(tokens[1], rune::TokenKind::TOK_PRINT, "print");
    assert_token(tokens[2], rune::TokenKind::TOK_IDENTIFIER, "not_keyword");
    assert(tokens.back().kind == rune::TokenKind::TOK_EOF);

    std::cout << "test_keywords PASSED\n";
}

void test_integers() {
    const std::string source = "1 432 943 not_integer";
    rune::Lexer lexer(source);

    std::vector<rune::Token> tokens;
    lexer.lex_all(tokens);

    assert(tokens.size() == 5);
    assert_token(tokens[0], rune::TokenKind::TOK_INT, "1");
    assert_token(tokens[1], rune::TokenKind::TOK_INT, "432");
    assert_token(tokens[2], rune::TokenKind::TOK_INT, "943");
    assert_token(tokens[3], rune::TokenKind::TOK_IDENTIFIER, "not_integer");
    assert(tokens.back().kind == rune::TokenKind::TOK_EOF);

    std::cout << "test_integers PASSED\n";
}

void test_comments() {
    const std::string source = "let x = 123;\n// skip all this\nlet y = 456;";
    rune::Lexer lexer(source);

    std::vector<rune::Token> tokens;
    lexer.lex_all(tokens);

    assert(tokens.size() == 11);
    assert_token(tokens[0], rune::TokenKind::TOK_LET, "let");
    assert_token(tokens[1], rune::TokenKind::TOK_IDENTIFIER, "x");
    assert_token(tokens[2], rune::TokenKind::TOK_EQUAL, "=");
    assert_token(tokens[3], rune::TokenKind::TOK_INT, "123");
    assert_token(tokens[4], rune::TokenKind::TOK_SEMICOLON, ";");
    assert_token(tokens[5], rune::TokenKind::TOK_LET, "let");
    assert_token(tokens[6], rune::TokenKind::TOK_IDENTIFIER, "y");
    assert_token(tokens[7], rune::TokenKind::TOK_EQUAL, "=");
    assert_token(tokens[8], rune::TokenKind::TOK_INT, "456");
    assert_token(tokens[9], rune::TokenKind::TOK_SEMICOLON, ";");
    assert(tokens.back().kind == rune::TokenKind::TOK_EOF);

    std::cout << "test_comments PASSED\n";
}

void test_operators_and_punctuation() {
    const std::string source = "+ - / * ( ) = ;";
    rune::Lexer lexer(source);

    std::vector<rune::Token> tokens;
    lexer.lex_all(tokens);

    assert(tokens.size() == 9);
    assert_token(tokens[0], rune::TokenKind::TOK_PLUS, "+");
    assert_token(tokens[1], rune::TokenKind::TOK_MINUS, "-");
    assert_token(tokens[2], rune::TokenKind::TOK_SLASH, "/");
    assert_token(tokens[3], rune::TokenKind::TOK_STAR, "*");
    assert_token(tokens[4], rune::TokenKind::TOK_LPAREN, "(");
    assert_token(tokens[5], rune::TokenKind::TOK_RPAREN, ")");
    assert_token(tokens[6], rune::TokenKind::TOK_EQUAL, "=");
    assert_token(tokens[7], rune::TokenKind::TOK_SEMICOLON, ";");
    assert(tokens.back().kind == rune::TokenKind::TOK_EOF);

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

    assert(tokens.size() == 9);

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

    assert(tokens.back().kind == rune::TokenKind::TOK_EOF);

    std::cout
        << "test_line_and_column_tracking PASSED\n";
}

void test_unknown_characters_produce_error() {
    const std::string source = ": \\ | `";
    rune::Lexer lexer(source);

    std::vector<rune::Token> tokens;
    lexer.lex_all(tokens);

    assert(tokens.size() == 5);
    assert_token(tokens[0], rune::TokenKind::TOK_ERROR, ":");
    assert_token(tokens[1], rune::TokenKind::TOK_ERROR, "\\");
    assert_token(tokens[2], rune::TokenKind::TOK_ERROR, "|");
    assert_token(tokens[3], rune::TokenKind::TOK_ERROR, "`");
    assert(tokens.back().kind == rune::TokenKind::TOK_EOF);
    
    std::cout
        << "test_unknown_characters_produce_error PASSED\n";
}

void test_empty_source_produces_only_eof() {
    const std::string source = "";
    rune::Lexer lexer(source);

    std::vector<rune::Token> tokens;
    lexer.lex_all(tokens);

    assert(tokens.size() == 1);
    assert(tokens.back().kind == rune::TokenKind::TOK_EOF);

     std::cout
        << "test_empty_source_produces_only_eof PASSED\n";
}

void test_slash_at_eof() {
    const std::string source = "/";
    rune::Lexer lexer(source);

    std::vector<rune::Token> tokens;
    lexer.lex_all(tokens);

    assert(tokens.size() == 2);
    assert_token(tokens[0], rune::TokenKind::TOK_SLASH, "/");
    assert(tokens.back().kind == rune::TokenKind::TOK_EOF);

    std::cout
        << "test_slash_at_eof PASSED\n";
}

void test_comment_at_eof() {
    const std::string source = "// comment without newline";
    rune::Lexer lexer(source);

    std::vector<rune::Token> tokens;
    lexer.lex_all(tokens);

    assert(tokens.size() == 1);
    assert(tokens.back().kind == rune::TokenKind::TOK_EOF);

    std::cout
        << "test_comment_at_eof PASSED\n";
}

void test_adjacent_integer_and_identifier() {
    const std::string source = "42abc";
    rune::Lexer lexer(source);

    std::vector<rune::Token> tokens;
    lexer.lex_all(tokens);

    assert(tokens.size() == 3);
    assert_token(tokens[0], rune::TokenKind::TOK_INT, "42");
    assert_token(tokens[1], rune::TokenKind::TOK_IDENTIFIER, "abc");
    assert(tokens.back().kind == rune::TokenKind::TOK_EOF);

    std::cout
        << "test_adjacent_integer_and_identifier PASSED\n";
}

void test_position_after_comment() {
    const std::string source =
        "// comment\n"
        "let x = 1;";
    rune::Lexer lexer(source);

    std::vector<rune::Token> tokens;
    lexer.lex_all(tokens);

    assert(tokens.size() == 6);
    assert(tokens[0].line == 2 && tokens[0].column == 1);
    assert(tokens[1].line == 2 && tokens[1].column == 5);
    assert(tokens[2].line == 2 && tokens[2].column == 7);
    assert(tokens[3].line == 2 && tokens[3].column == 9);
    assert(tokens[4].line == 2 && tokens[4].column == 10);
    assert(tokens.back().kind == rune::TokenKind::TOK_EOF);

    std::cout
        << "test_position_after_comment PASSED\n";
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
    test_slash_at_eof();
    test_comment_at_eof();
    test_adjacent_integer_and_identifier();
    test_position_after_comment();
}
