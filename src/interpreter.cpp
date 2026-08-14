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

    throw std::runtime_error("Unsupported expression type");
}

} // namespace rune
