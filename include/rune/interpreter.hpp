#ifndef RUNE_INTERPRETER_HPP
#define RUNE_INTERPRETER_HPP

#include "ast.hpp"

namespace rune 
{

class Interpreter {
public:
    int evaluate(const Expr& expr);
};

} // namespace rune

#endif
