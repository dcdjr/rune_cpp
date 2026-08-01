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

} // namespace rune
