#pragma once
#include "Automaton.h"

class BadString : public Automaton
{
    public:
        BadString(TokenType tokenType) { this->type = tokenType; };
 //       ~BadString();
        int Start(const std::string& input);
};
