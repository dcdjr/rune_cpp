#include "rune/interpreter.hpp"
#include "rune/ast.hpp"
#include <iostream>
#include <cassert>
#include <string>

void run_tests();

int main() {
    run_tests();
}

// Expression evaluation tests
void test_interpreter_evaluates_integer_expression() {
    const rune::IntegerExpr int_expr(42);

    rune::Interpreter interpreter;

    int int_expr_value = interpreter.evaluate(int_expr);

    assert(int_expr_value == 42);

    std::cout
        << "test_interpreter_evaluates_integer_expression PASSED\n";
}

void test_interpreter_plus_op() {
    std::unique_ptr<rune::Expr> left =
        std::make_unique<rune::IntegerExpr>(8);

    rune::Token op = rune::Token{
        rune::TokenKind::TOK_PLUS,
        "+",
        1,
        3
    };

    std::unique_ptr<rune::Expr> right =
        std::make_unique<rune::IntegerExpr>(2);


    const rune::BinaryExpr binary_expr(
        std::move(left),
        op,
        std::move(right)
    );

    rune::Interpreter interpreter;

    int value = interpreter.evaluate(binary_expr);

    assert(value == 10);

    std::cout
        << "test_interpreter_plus_op PASSED\n";
}

void test_interpreter_minus_op() {
    std::unique_ptr<rune::Expr> left =
        std::make_unique<rune::IntegerExpr>(8);

    rune::Token op = rune::Token{
        rune::TokenKind::TOK_MINUS,
        "-",
        1,
        3
    };

    std::unique_ptr<rune::Expr> right =
        std::make_unique<rune::IntegerExpr>(2);


    const rune::BinaryExpr binary_expr(
        std::move(left),
        op,
        std::move(right)
    );

    rune::Interpreter interpreter;

    int value = interpreter.evaluate(binary_expr);

    assert(value == 6);

    std::cout
        << "test_interpreter_minus_op PASSED\n";
}

void test_interpreter_multiply_op() {
    std::unique_ptr<rune::Expr> left =
        std::make_unique<rune::IntegerExpr>(8);

    rune::Token op = rune::Token{
        rune::TokenKind::TOK_STAR,
        "*",
        1,
        3
    };

    std::unique_ptr<rune::Expr> right =
        std::make_unique<rune::IntegerExpr>(2);


    const rune::BinaryExpr binary_expr(
        std::move(left),
        op,
        std::move(right)
    );

    rune::Interpreter interpreter;

    int value = interpreter.evaluate(binary_expr);

    assert(value == 16);

    std::cout
        << "test_interpreter_multiply_op PASSED\n";
}

void test_interpreter_divide_op() {
    std::unique_ptr<rune::Expr> left =
        std::make_unique<rune::IntegerExpr>(8);

    rune::Token op = rune::Token{
        rune::TokenKind::TOK_SLASH,
        "/",
        1,
        3
    };

    std::unique_ptr<rune::Expr> right =
        std::make_unique<rune::IntegerExpr>(2);


    const rune::BinaryExpr binary_expr(
        std::move(left),
        op,
        std::move(right)
    );

    rune::Interpreter interpreter;

    int value = interpreter.evaluate(binary_expr);

    assert(value == 4);

    std::cout
        << "test_interpreter_divide_op PASSED\n";
}

void test_interpreter_evaluates_nested_binary_exprs() {
    std::unique_ptr<rune::Expr> node_2 =
        std::make_unique<rune::IntegerExpr>(2);

    rune::Token op_plus = rune::Token{
        rune::TokenKind::TOK_PLUS,
        "+",
        1,
        3
    };

    std::unique_ptr<rune::Expr> node_3 =
        std::make_unique<rune::IntegerExpr>(3);

    rune::Token op_multiply = rune::Token{
        rune::TokenKind::TOK_STAR,
        "*",
        1,
        7
    };

    std::unique_ptr<rune::Expr> node_4 =
        std::make_unique<rune::IntegerExpr>(4);

    std::unique_ptr<rune::Expr> binary_expr_multiply =
        std::make_unique<rune::BinaryExpr>(
            std::move(node_3),
            op_multiply,
            std::move(node_4)
        );

    const rune::BinaryExpr binary_expr_plus(
        std::move(node_2),
        op_plus,
        std::move(binary_expr_multiply)
    );

    rune::Interpreter interpreter;

    int value = interpreter.evaluate(binary_expr_plus);

    assert(value == 14);

    std::cout
        << "test_interpreter_evaluates_nested_binary_exprs PASSED\n";
}

void test_interpreter_throws_divide_by_zero_error() {
    std::unique_ptr<rune::Expr> left =
        std::make_unique<rune::IntegerExpr>(10);

    rune::Token op = rune::Token{
        rune::TokenKind::TOK_SLASH,
        "/",
        1,
        3
    };

    std::unique_ptr<rune::Expr> right =
        std::make_unique<rune::IntegerExpr>(0);


    const rune::BinaryExpr binary_expr(
        std::move(left),
        op,
        std::move(right)
    );

    rune::Interpreter interpreter;

    bool threw = false;

    try {
        interpreter.evaluate(binary_expr);    
    } catch (const std::runtime_error& e) {
        threw = true;
        assert(
            std::string(e.what()) ==
            "Error: divide by 0"
        );
    }

    assert(threw);

    std::cout
        << "test_interpreter_throws_divide_by_zero_error PASSED\n";
}

void test_defined_variable() {
    rune::Interpreter interpreter;

    interpreter.define("x", 42);

    const rune::Token name = rune::Token{
        rune::TokenKind::TOK_IDENTIFIER,
        "x",
        1,
        1
    };

    const rune::VariableExpr var(name);

    int value = interpreter.evaluate(var);

    assert(value == 42);

    std::cout
        << "test_defined_variable PASSED\n";
}

void test_defined_variable_inside_binary_expr() {
    rune::Interpreter interpreter;

    interpreter.define("x", 10);

    const rune::Token name = rune::Token{
        rune::TokenKind::TOK_IDENTIFIER,
        "x",
        1,
        1
    };

    std::unique_ptr<rune::Expr> left =
        std::make_unique<rune::VariableExpr>(name);

    std::unique_ptr<rune::Expr> right =
        std::make_unique<rune::IntegerExpr>(5);

    const rune::Token op_plus = rune::Token{
        rune::TokenKind::TOK_PLUS,
        "+",
        1,
        3
    };

    rune::BinaryExpr binary_expr(
        std::move(left),
        op_plus,
        std::move(right)
    );

    int value = interpreter.evaluate(binary_expr);

    assert(value == 15);

    std::cout
        << "test_defined_variable_inside_binary_expr PASSED\n";
}

void test_undefined_variable_throws_error() {
    rune::Interpreter interpreter;

    const rune::Token name = rune::Token{
        rune::TokenKind::TOK_IDENTIFIER,
        "x",
        1,
        1
    };

    const rune::VariableExpr var(name);

    bool threw = false;

    try {
        interpreter.evaluate(var);
    } catch (const std::runtime_error& e) {
        threw = true;
        assert(
            std::string(e.what()) ==
            "Error: Undefined variable: \"x\""
        );
    }

    assert(threw);

    std::cout
        << "test_undefined_variable_throws_error PASSED\n";
}

// Statement execution tests
void test_interpreter_executes_let_statement() {
    rune::Interpreter interpreter;

    std::unique_ptr<rune::Expr> initializer =
        std::make_unique<rune::IntegerExpr>(42);

    const rune::Token name = rune::Token{
        rune::TokenKind::TOK_IDENTIFIER,
        "x",
        1,
        5
    };

    const rune::LetStmt let_stmt(name, std::move(initializer));

    interpreter.execute(let_stmt);

    rune::VariableExpr var(name);

    int value = interpreter.evaluate(var);

    assert(value == 42);

    std::cout
        << "test_interpreter_executes_let_statement PASSED\n";
}

void run_tests() {
    test_interpreter_evaluates_integer_expression();
    test_interpreter_plus_op();
    test_interpreter_minus_op();
    test_interpreter_multiply_op();
    test_interpreter_divide_op();
    test_interpreter_evaluates_nested_binary_exprs();
    test_interpreter_throws_divide_by_zero_error();
    test_defined_variable();
    test_undefined_variable_throws_error();
    test_defined_variable_inside_binary_expr();
    test_interpreter_executes_let_statement();
} 
