#ifndef RUNE_PARSER_HPP 
#define RUNE_PARSER_HPP 

#include "rune/token.hpp"
#include "rune/ast.hpp"
#include <memory>

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


public:
    explicit Parser(const std::vector<Token>& tokens_)
        : tokens_(tokens_), current_(0) {}

    std::unique_ptr<Expr> parse_factor();
};

} // namespace rune

#endif
