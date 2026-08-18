#include "rune/ast.hpp"

namespace rune 
{

/* Expr AST Nodes */

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

/* Stmt AST Nodes */

// LetStmt functions
const Token& LetStmt::name() const {
    return name_;
}

const Expr& LetStmt::initializer() const {
    return *initializer_;
}

// PrintStmt functions
const Expr& PrintStmt::expression() const {
    return *expression_;
}

// ReassignStmt functions
const Token& ReassignStmt::name() const {
    return name_;
}

const Expr& ReassignStmt::reinitializer() const {
    return *reinitializer_;
}

} // namespace rune

