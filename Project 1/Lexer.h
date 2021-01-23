#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include "Token.h"
#include "Automaton.h"
#include "MatcherAutomaton.h"

class Lexer {
    private:
        std::vector<Token*> tokens;
        std::vector<Automaton*> automata;

        std::string removeWhiteSpace(std::string inputString);

    public:
        Lexer() {
            tokens = std::vector<Token*>();
            automata = std::vector<Automaton*>();

 //           automata.push_back(new MatcherAutomaton(":", COMMA));
            
        };

        ~Lexer();

        void Run(std::string inputString);
};