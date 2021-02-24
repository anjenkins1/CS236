#pragma once
#include "Automaton.h"

class BadComment : public Automaton
{
    public:
        BadComment(TokenType tokenType) { this->type = tokenType; };
      //  ~BadComment();
        int Start(const std::string& input);
        
};