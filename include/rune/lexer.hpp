#ifndef RUNE_LEXER_HPP
#define RUNE_LEXER_HPP

#include "token.hpp"

#include <cstddef>
#include <string_view>

namespace rune 
{

class Lexer {
private:
    std::string_view source_;
    std::size_t pos_;
    std::size_t line_;
    std::size_t column_;

    bool is_at_end() const;
    char peek() const;
    char advance();
    void skip_whitespace();

    Token scan_identifier(
        std::size_t start_pos,
        std::size_t start_line,
        std::size_t start_column
    );

    Token scan_integer(
        std::size_t start_pos,
        std::size_t start_line,
        std::size_t start_column
    );

    Token make_token(
        TokenKind kind,
        std::size_t start_pos,
        std::size_t start_line,
        std::size_t start_column
    ) const;

    Token make_eof_token(
        std::size_t start_line,
        std::size_t start_column
    ) const;

public:
    explicit Lexer(std::string_view source);

    Token next_token();

};

} // namespace rune

#endif
