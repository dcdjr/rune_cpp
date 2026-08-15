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

    if (auto *variable =
            dynamic_cast<const VariableExpr*>(&expr)) {
        std::string name(variable->name().lexeme);

        auto it = environment_.find(name);
        if (it == environment_.end())
            throw std::runtime_error("Error: Undefined variable: \"" + name + "\"");
        return it->second;
    }

    throw std::runtime_error("Error: Unsupported expression type");
}

void Interpreter::define(const std::string& name, int value) {
    environment_[name] = value;
}

} // namespace rune
