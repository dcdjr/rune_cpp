#include "rune/interpreter.hpp"
#include "rune/ast.hpp"
#include <stdexcept>

namespace rune 
{

int Interpreter::evaluate(const Expr& expr) {
    if (auto *integer = 
            dynamic_cast<const IntegerExpr*>(&expr)) {
        return integer->value();
    }

    if (auto *binary =
            dynamic_cast<const BinaryExpr*>(&expr)) {
        int left_value = evaluate(binary->left());
        int right_value = evaluate(binary->right());

        switch (binary->op().kind) {
            case TokenKind::TOK_PLUS:
                return left_value + right_value;
            case TokenKind::TOK_MINUS:
                return left_value - right_value;
            case TokenKind::TOK_STAR:
                return left_value * right_value;
            case TokenKind::TOK_SLASH:
                if (right_value == 0)
                    throw std::runtime_error(
                        "Error: divide by 0"
                    );
                return left_value / right_value;
            default:
                throw std::runtime_error("Error: Unsupported operator");
        }
    }

    throw std::runtime_error("Error: Unsupported expression type");
}

} // namespace rune
