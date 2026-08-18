#ifndef RUNE_INTERPRETER_HPP
#define RUNE_INTERPRETER_HPP

#include "ast.hpp"
#include <unordered_map>
#include <string>
#include <iostream>

namespace rune 
{

class Interpreter {
private:
    std::unordered_map<std::string, int> environment_;
    std::ostream& output_;

public:
    explicit Interpreter(std::ostream& output)
        : output_(output) {}

    int evaluate(const Expr& expr);
    void execute(const Stmt& stmt);
    void define(const std::string& name, int value);

    void interpret(const std::vector<std::unique_ptr<Stmt>>& statements);
};

} // namespace rune

#endif
