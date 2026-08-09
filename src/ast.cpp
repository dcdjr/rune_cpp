#include "rune/ast.hpp"

namespace rune 
{

const Expr& BinaryExpr::left() const {
    return *left_;
}

const Expr& BinaryExpr::right() const {
    return *right_;
}

const Token& BinaryExpr::op() const {
    return op_;
}

} // namespace rune

