#pragma once
#include "Automaton.h"

class StringAutomaton : public Automaton
{
    public:
        StringAutomaton(TokenType tokenType) { this->type = tokenType; };
   //     ~StringAutomaton();
        int Start(const std::string& input);
};
