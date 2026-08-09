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
    std::unique_ptr<Expr> left_;
    Token op_;
    std::unique_ptr<Expr> right_;

public:
    BinaryExpr(
        std::unique_ptr<Expr> left_,
        Token op_,
        std::unique_ptr<Expr> right_
    ) : left_(std::move(left_)), op_(op_), right_(std::move(right_)) {}

    const Expr& left() const;
    const Expr& right() const;
    const Token& op() const;
};

} // namespace rune

#endif
