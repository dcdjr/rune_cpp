#ifndef RUNE_TOKEN_HPP
#define RUNE_TOKEN_HPP

#include <cstddef>
#include <string_view>

namespace rune
{

enum class TokenKind {
    TOK_PRINT,

    TOK_INT,

    TOK_SEMICOLON,

    TOK_PLUS,
    TOK_MINUS,
    TOK_STAR,
    TOK_SLASH,

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

} // rune namespace


#endif
