#include "rune/lexer.hpp"
#include "rune/token.hpp"
#include "rune/parser.hpp"
#include "rune/interpreter.hpp"
#include "rune/file_utils.hpp"
#include <iostream>
#include <vector>
#include <string>

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: ./runec <input_file>" << '\n'; 
        return 1;
    }

    const auto program = rune::load_program(argv[1]);
    
    if (!program) {
        std::cerr 
            << "Unable to open file "
            << "\"" << argv[1] << "\""
            << '\n'; 
        return 1;
    }

    rune::Lexer lexer(program.value());

    std::vector<rune::Token> tokens;
    lexer.lex_all(tokens);

    rune::Parser parser(tokens);

    auto statements = parser.parse_program();

    rune::Interpreter interpreter(std::cout);

    interpreter.interpret(statements);

    return 0;
}
