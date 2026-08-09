#include "rune/ast.hpp"
#include "rune/parser.hpp"
#include <memory>
#include <string>
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

std::unique_ptr<Expr> Parser::parse_factor() {
    if (check(TokenKind::TOK_INT)) {
        const Token& current = advance();
        int value = std::stoi(std::string(current.lexeme));
        return std::make_unique<IntegerExpr>(value);
    }
    throw std::runtime_error("Expected expression");
}

std::unique_ptr<Expr> Parser::parse_term() {
    std::unique_ptr<Expr> left = parse_factor();

    while (
        check(TokenKind::TOK_STAR) ||
        check(TokenKind::TOK_SLASH)
    ) {
        Token op = advance();
        std::unique_ptr<Expr> right = parse_factor();

        left = std::make_unique<BinaryExpr>(
            std::move(left),
            op,
            std::move(right)
        );
    }

    return left;
}

} // namespace rune

