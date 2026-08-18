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

void Interpreter::execute(const Stmt& stmt) {
    if (auto *let_stmt = 
            dynamic_cast<const LetStmt*>(&stmt)) {
        int value = evaluate(let_stmt->initializer());
        define(std::string(let_stmt->name().lexeme), value);
        return;
    }

    if (auto *print_stmt =
            dynamic_cast<const PrintStmt*>(&stmt)) {
        int value = evaluate(print_stmt->expression());
        output_ << value << "\n";
        return;
    }

    if (auto *reassign_stmt =
            dynamic_cast<const ReassignStmt*>(&stmt)) {
        std::string name(reassign_stmt->name().lexeme);
        auto it = environment_.find(name);
        if (it == environment_.end())
            throw std::runtime_error("Error: Reassignment of nonexistent variable");

        int reassignment_value = evaluate(reassign_stmt->reinitializer());
        define(name, reassignment_value);         
        return;
    }

    throw std::runtime_error("Error: Unsupported statement type");
}

void Interpreter::define(const std::string& name, int value) {
    environment_[name] = value;
}

void Interpreter::interpret(const std::vector<std::unique_ptr<Stmt>>& statements) {
    for (const auto& stmt : statements) {
        execute(*stmt);
    }
}

} // namespace rune
