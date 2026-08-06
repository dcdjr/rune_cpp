#ifndef RUNE_TOKEN_HPP
#define RUNE_TOKEN_HPP

#include <cstddef>
#include <string_view>
#include <vector>

namespace rune
{

enum class TokenKind {
    TOK_IDENTIFIER,
    TOK_PRINT,
    TOK_LET,

    TOK_COMMENT,

    TOK_INT,

    TOK_SEMICOLON,

    TOK_PLUS,
    TOK_MINUS,
    TOK_STAR,
    TOK_SLASH,
    TOK_EQUAL,

    TOK_LPAREN,
    TOK_RPAREN,

    TOK_ERROR,
    TOK_EOF
};

struct Token {
    TokenKind kind;
    std::string_view lexeme;
    std::size_t line;
    std::size_t column;
};

void print_token(const Token& token);
void print_all_tokens(
    const std::vector<rune::Token>& tokens 
);

} // rune namespace


#endif
