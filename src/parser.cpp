#include "rune/parser.hpp"
#include <stdexcept>

namespace rune 
{

const Token& Parser::peek() const {
    if (current_ >= tokens_.size()) {
        throw std::out_of_range("Parser cursor moved past token stream");
    }

    return tokens_[current_];
}

bool Parser::is_at_end() const {
    return peek().kind == TokenKind::TOK_EOF;
}

const Token& Parser::advance() {
    const Token& current = peek();

    if (!is_at_end()) {
        current_++;
    }

    return current;
}

bool Parser::check(TokenKind kind) const {
    return peek().kind == kind;
}

bool Parser::match(TokenKind kind) {
    if (check(kind)) {
        advance();
        return true;
    }
    return false;
}

} // namespace rune

