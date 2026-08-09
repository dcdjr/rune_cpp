#ifndef RUNE_AST_HPP
#define RUNE_AST_HPP

#include "rune/token.hpp"
#include <memory>
#include <utility>

namespace rune 
{

class Expr {
public:
    virtual ~Expr() = default;
};

class IntegerExpr : public Expr {
private:
    int value;

public:
    explicit IntegerExpr(int value)
        : value(value) {}
};

class BinaryExpr : public Expr {
private:
    std::unique_ptr<Expr> left;
    Token op;
    std::unique_ptr<Expr> right;

public:
    BinaryExpr(
        std::unique_ptr<Expr> left,
        std::unique_ptr<Expr> right,
        Token op
    ) : left(std::move(left)), op(op), right(std::move(right)) {}
};

} // namespace rune

#endif
