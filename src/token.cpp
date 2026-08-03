#include "rune/token.hpp"
#include <string>
#include <iostream>

void rune::print_token(rune::Token tok) {
    std::string kind = "";

    switch (tok.kind) {
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

    std::cout 
        << kind
        << " \"" << tok.lexeme << "\""
        << " at " << tok.line << ":" << tok.column
        << '\n';
}
