#ifndef RUNE_INTERPRETER_HPP
#define RUNE_INTERPRETER_HPP

#include "ast.hpp"
#include <unordered_map>
#include <string>

namespace rune 
{

class Interpreter {
private:
    std::unordered_map<std::string, int> environment_;

public:
    int evaluate(const Expr& expr);
    void define(const std::string& name, int value);
};

} // namespace rune

#endif
