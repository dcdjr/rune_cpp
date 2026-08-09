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
    int value_;

public:
    explicit IntegerExpr(int value_)
        : value_(value_) {}

    int value() const {
        return value_;
    }
};

class BinaryExpr : public Expr {
private:
    std::unique_ptr<Expr> left;
    Token op;
    std::unique_ptr<Expr> right;

public:
    BinaryExpr(
        std::unique_ptr<Expr> left,
        Token op,
        std::unique_ptr<Expr> right
    ) : left(std::move(left)), op(op), right(std::move(right)) {}
};

} // namespace rune

#endif
