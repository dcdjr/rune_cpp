#ifndef RUNE_PARSER_HPP 
#define RUNE_PARSER_HPP 

#include "rune/token.hpp"
#include "rune/ast.hpp"
#include <memory>
#include <string>

namespace rune
{

class Parser {
private:
    const std::vector<Token>& tokens_;
    std::size_t current_;

    const Token& peek() const;
    bool is_at_end() const;
    const Token& advance();
    bool check(TokenKind kind) const;
    bool match(TokenKind kind);

    // Helpers
    const Token& consume(TokenKind kind, const std::string& message);

public:
    explicit Parser(const std::vector<Token>& tokens_)
        : tokens_(tokens_), current_(0) {}

    // Expression parsing
    std::unique_ptr<Expr> parse_factor();
    std::unique_ptr<Expr> parse_term();
    std::unique_ptr<Expr> parse_expression();

    // Statement parsing
    std::unique_ptr<Stmt> parse_let_statement();
    std::unique_ptr<Stmt> parse_statement();
};

} // namespace rune

#endif
