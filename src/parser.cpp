#include "rune/ast.hpp"
#include "rune/parser.hpp"
#include <memory>
#include <string>
#include <stdexcept>

namespace rune 
{

// Parser helper methods
const Token& Parser::consume(TokenKind kind, const std::string& message) {
    if (peek().kind == kind)
        return advance();

    throw std::runtime_error(message);
}

// Parser private methods
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

// Parser expression methods
std::unique_ptr<Expr> Parser::parse_factor() {
    if (check(TokenKind::TOK_INT)) {
        const Token& current = advance();
        int value = std::stoi(std::string(current.lexeme));
        return std::make_unique<IntegerExpr>(value);
    }

    if (check(TokenKind::TOK_IDENTIFIER)) {
        const Token& current = advance();
        return std::make_unique<VariableExpr>(current);
    }
    
    if (check(TokenKind::TOK_LPAREN)) {
        advance();

        auto expr = parse_expression();

        if (!match(TokenKind::TOK_RPAREN)) {
            throw std::runtime_error("Expected right parenthesis");
        }

        return expr;
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

std::unique_ptr<Expr> Parser::parse_expression() {
    std::unique_ptr<Expr> left = parse_term();

    while (
        check(TokenKind::TOK_PLUS) ||
        check(TokenKind::TOK_MINUS)
    ) {
        Token op = advance();
        std::unique_ptr<Expr> right = parse_term();

        left = std::make_unique<BinaryExpr>(
            std::move(left),
            op,
            std::move(right)
        );
    }

    return left;
}

// Parser statement methods
std::unique_ptr<Stmt> Parser::parse_let_statement() {
    consume(TokenKind::TOK_LET, "Expected \"let\"");
    Token name = consume(TokenKind::TOK_IDENTIFIER, "Expected identifier");
    consume(TokenKind::TOK_EQUAL, "Expected \"=\"");
    std::unique_ptr<Expr> initializer = parse_expression();
    consume(TokenKind::TOK_SEMICOLON, "Expected \";\"");

    return std::make_unique<LetStmt>(
        name,
        std::move(initializer)
    );
}


} // namespace rune

