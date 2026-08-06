#include "rune/lexer.hpp"
#include "rune/token.hpp"
#include "rune/file_utils.hpp"
#include <iostream>
#include <vector>
#include <string>

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: ./runec <input_file>" << '\n'; 
        return 1;
    }

    const std::string program = rune::load_program(argv[1]);
    
    if (program == "") {
        std::cerr 
            << "Unable to open file "
            << "\"" << argv[1] << "\""
            << '\n'; 
        return 1;
    }

    rune::Lexer lexer(program);

    std::vector<rune::Token> tok_vec;
    lexer.lex_all(tok_vec);

    print_all_tokens(tok_vec);

    return 0;
}
