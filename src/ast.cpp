#include "rune/ast.hpp"

namespace rune 
{

// IntegerExpr functions
int IntegerExpr::value() const {
    return value_;
}

// BinaryExpr functions
const Expr& BinaryExpr::left() const {
    return *left_;
}

const Expr& BinaryExpr::right() const {
    return *right_;
}

const Token& BinaryExpr::op() const {
    return op_;
}

// VariableExpr functions
const Token& VariableExpr::name() const {
    return name_;
}

} // namespace rune

