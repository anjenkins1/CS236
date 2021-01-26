#pragma once
#include "Automaton.h"

class CommentAutomaton : public Automaton
{
    public:
        CommentAutomaton(TokenType tokenType) { this->type = tokenType; };
//        ~CommentAutomaton();
        int Start(const std::string& input);
        
};
