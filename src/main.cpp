#include "rune/lexer.hpp"
#include "rune/token.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: ./runec <input_file>" << '\n'; 
        return 1;
    }

    std::ifstream ifs(argv[1]);

    if (!ifs.is_open()) {
        std::cerr 
            << "Unable to open file "
            << "\"" << argv[1] << "\""
            << '\n'; 
        return 1;
    }

    std::stringstream ss;
    ss << ifs.rdbuf();
    std::string program = ss.str();

    std::vector<rune::Token> tok_vec;
    rune::Lexer lexer(program);

    while (true) {
        rune::Token tok = lexer.next_token();

        tok_vec.push_back(tok);

        if (tok.kind == rune::TokenKind::TOK_EOF) {
            break;
        }
    }

    for (const auto& t : tok_vec) {
        rune::print_token(t);
    }

    return 0;
}
