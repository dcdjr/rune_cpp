#include "rune/token.hpp"
#include <string>
#include <iostream>
#include <vector>

void rune::print_token(const rune::Token& token) {
    std::string kind = "";

    switch (token.kind) {
        case rune::TokenKind::TOK_EOF:
            kind = "TOK_EOF";
            break;
        case rune::TokenKind::TOK_SEMICOLON:
            kind = "TOK_SEMICOLON";
            break;
        case rune::TokenKind::TOK_ERROR:
            kind = "TOK_ERROR";
            break;
        case rune::TokenKind::TOK_INT:
            kind = "TOK_INT";
            break;
        case rune::TokenKind::TOK_LPAREN:
            kind = "TOK_LPAREN";
            break;
        case rune::TokenKind::TOK_RPAREN:
            kind = "TOK_RPAREN";
            break;
        case rune::TokenKind::TOK_MINUS:
            kind = "TOK_MINUS";
            break;
        case rune::TokenKind::TOK_PLUS:
            kind = "TOK_PLUS";
            break;
        case rune::TokenKind::TOK_STAR:
            kind = "TOK_STAR";
            break;
        case rune::TokenKind::TOK_SLASH:
            kind = "TOK_SLASH";
            break;
        case rune::TokenKind::TOK_EQUAL:
            kind = "TOK_EQUAL";
            break;
        case rune::TokenKind::TOK_IDENTIFIER:
            kind = "TOK_IDENTIFIER";
            break;
        case rune::TokenKind::TOK_PRINT:
            kind = "TOK_PRINT";
            break;
        case rune::TokenKind::TOK_LET:
            kind = "TOK_LET";
            break;
        default:
            kind = "UNKNOWN";
    }

    if (token.kind != rune::TokenKind::TOK_EOF) {
        std::cout 
            << kind
            << " \"" << token.lexeme << "\""
            << " at " << token.line << ":" << token.column
            << '\n';
    } else {
        std::cout << kind << '\n';
    }
}

void rune::print_all_tokens(
    const std::vector<rune::Token>& tokens
) {
        for (const auto& token : tokens) {
        rune::print_token(token);
    }
}
