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
    explicit IntegerExpr(int value)
        : value_(value) {}

    int value() const;
};

class BinaryExpr : public Expr {
private:
    std::unique_ptr<Expr> left_;
    Token op_;
    std::unique_ptr<Expr> right_;

public:
    BinaryExpr(
        std::unique_ptr<Expr> left,
        Token op,
        std::unique_ptr<Expr> right
    ) : left_(std::move(left)), op_(op), right_(std::move(right)) {}

    const Expr& left() const;
    const Expr& right() const;
    const Token& op() const;
};

class VariableExpr : public Expr {
private:
    Token name_;

public:
    explicit VariableExpr(Token name)
        : name_(name) {}

    const Token& name() const;
};

} // namespace rune

#endif
