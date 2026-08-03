#include "rune/lexer.hpp"
#include "rune/token.hpp"
#include <iostream>
#include <vector>
#include <string>

int main() {
    std::string example1 = "   +-*/ age();";
    std::string example2 = "a age age2 _value print let foo_bar + abc;";
    std::string example3 = "let age = 19;\nprint age;";

    std::vector<rune::Token> tok_vec;

    rune::Lexer lexer(example3);

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
