#include "rune/lexer.hpp"
#include "rune/token.hpp"
#include <vector>

namespace rune
{

// Line and column start at human-readable 1. Absolute position starts at 0.
Lexer::Lexer(std::string_view source)
    : source_(source), pos_(0), line_(1), column_(1) {}

// Returns true if lexer is looking past the end of the source buffer.
bool Lexer::is_at_end() const {
    return pos_ >= source_.size();
}

// Returns the character the lexer is currently looking at.
char Lexer::peek() const {
    if (is_at_end()) return '\0';
    return source_[pos_];
}

char Lexer::advance() {
    if (is_at_end()) return '\0';

    const char current = source_[pos_];
    pos_++;

    if (current == '\n') {
        line_++;
        column_ = 1;
    } else {
        column_++;
    }

    return current;
}

static bool is_whitespace(char c) {
    return (c == ' ')  ||
           (c == '\t') ||
           (c == '\n') ||
           (c == '\r');
}

void Lexer::skip_whitespace() {
    while (!is_at_end()) {
        const char current = peek();

        if (is_whitespace(current))
            advance();
        else
            break;
    }
}

static bool is_identifier_start(char c) {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           (c == '_');
}

static bool is_identifier_continue(char c) {
    return is_identifier_start(c) ||
           (c >= '0' && c <= '9');
}

Token Lexer::scan_identifier(
    std::size_t start_pos,
    std::size_t start_line,
    std::size_t start_column
) {
    while (is_identifier_continue(peek())) {
        advance();
    }

    const std::string_view lexeme =
        source_.substr(start_pos, pos_ - start_pos);

    if (lexeme == "print") {
        return make_token(
            TokenKind::TOK_PRINT,
            start_pos,
            start_line,
            start_column
        );
    } else if (lexeme == "let") {
        return make_token(
            TokenKind::TOK_LET,
            start_pos,
            start_line,
            start_column
        );
    } else {
        return make_token(
            TokenKind::TOK_IDENTIFIER,
            start_pos,
            start_line,
            start_column
        );
    }
}

static bool is_digit(char c) {
    return c >= '0' && c <= '9';
}

Token Lexer::scan_integer(
    std::size_t start_pos,
    std::size_t start_line,
    std::size_t start_column
) {
    while (is_digit(peek())) {
        advance();
    }

    return make_token(
        TokenKind::TOK_INT,
        start_pos,
        start_line,
        start_column
    );
}

Token Lexer::make_token(
    TokenKind kind,
    std::size_t start_pos,
    std::size_t start_line,
    std::size_t start_column
) const {
    return Token{
        kind,
        source_.substr(start_pos, pos_ - start_pos),
        start_line,
        start_column
    };
}

Token Lexer::make_eof_token(
    std::size_t start_line,
    std::size_t start_column
) const {
    return Token{
        TokenKind::TOK_EOF,
        std::string_view{},
        start_line,
        start_column
    };
}

Token Lexer::next_token() {
    skip_whitespace();

    const std::size_t start_pos = pos_;
    const std::size_t start_line = line_;
    const std::size_t start_column = column_;

    if (is_at_end()) {
        return make_eof_token(
            start_line,
            start_column
        );
    }

    const char current = advance();

    if (is_identifier_start(current)) {
        return scan_identifier(
            start_pos,
            start_line,
            start_column
        );
    }

    if (is_digit(current)) {
        return scan_integer(
            start_pos,
            start_line,
            start_column
        );
    }

    switch (current) {
        case ';':
            return make_token(
                TokenKind::TOK_SEMICOLON,
                start_pos,
                start_line,
                start_column
            );
        case '+':
            return make_token(
                TokenKind::TOK_PLUS,
                start_pos,
                start_line,
                start_column
            );
        case '-':
            return make_token(
                TokenKind::TOK_MINUS,
                start_pos,
                start_line,
                start_column
            );
        case '*':
            return make_token(
                TokenKind::TOK_STAR,
                start_pos,
                start_line,
                start_column
            );
        case '/':
            return make_token(
                TokenKind::TOK_SLASH,
                start_pos,
                start_line,
                start_column
            );
        case '=':
            return make_token(
                TokenKind::TOK_EQUAL,
                start_pos,
                start_line,
                start_column
            );
        case '(':
            return make_token(
                TokenKind::TOK_LPAREN,
                start_pos,
                start_line,
                start_column
            );
        case ')':
            return make_token(
                TokenKind::TOK_RPAREN,
                start_pos,
                start_line,
                start_column
            );
        default:
            return make_token(
                TokenKind::TOK_ERROR,
                start_pos,
                start_line,
                start_column
            );
    }
}

void Lexer::lex_all(std::vector<Token>& tok_vec) {
    while (true) {
        rune::Token tok = next_token();
        tok_vec.push_back(tok);
        if (tok.kind == rune::TokenKind::TOK_EOF)
            break;
    } 
}

} // namespace rune
