#include "rune/lexer.hpp"
#include "rune/token.hpp"
#include <iostream>
#include <vector>
#include <string>

int main() {
    std::string example = "   +-*/ a();";

    std::vector<rune::Token> tok_vec;

    rune::Lexer lexer(example);

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
