#ifndef RUNE_PARSER_HPP 
#define RUNE_PARSER_HPP 

#include "rune/token.hpp"

namespace rune
{

class Parser {
private:
    const std::vector<Token>& tokens_;
    std::size_t current_;

public:
    explicit Parser(const std::vector<Token>& tokens_)
        : tokens_(tokens_), current_(0) {}


};

}

#endif
