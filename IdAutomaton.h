#pragma once
#include <cctype>
#include "Automaton.h"

class IdAutomaton : public Automaton
{
    public:
        IdAutomaton(TokenType tokenType) { this->type = tokenType; };
//     ~IdAutomaton();
        int Start(const std::string& input);
};