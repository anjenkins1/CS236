#pragma once
#include "Automaton.h"

class MatcherAutomaton : public Automaton
{
    private:
        std::string toMatch;
    public:
        MatcherAutomaton(std::string toMatch, TokenType tokenType);
        int Start(const std::string& input);
};
