#include "rune/interpreter.hpp"
#include "rune/ast.hpp"
#include <iostream>
#include <cassert>

void run_tests();

int main() {
    run_tests();
}

void test_interpreter_evaluates_integer_expression() {
    const rune::IntegerExpr int_expr(42);

    rune::Interpreter interpreter;

    int int_expr_value = interpreter.evaluate(int_expr);

    assert(int_expr_value == 42);

    std::cout
        << "test_interpreter_evaluates_integer_expression PASSED\n";
}

void run_tests() {
    test_interpreter_evaluates_integer_expression();
} 
