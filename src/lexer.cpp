#include "rune/lexer.hpp"

rune::Lexer::Lexer(std::string_view source)
    : source_(source), pos_(0), line_(1), column_(1) {}

bool rune::Lexer::is_at_end() const {
    return pos_ >= source_.size();
}
