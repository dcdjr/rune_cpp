#include "rune/lexer.hpp"

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

} // namespace rune
