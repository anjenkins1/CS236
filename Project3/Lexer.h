#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <sstream>
#include "Token.h"
#include "Automaton.h"
#include "MatcherAutomaton.h"
#include "StringAutomaton.h"
#include "CommentAutomaton.h"
#include "BadComment.h"
#include "BadString.h"
#include "IdAutomaton.h"

class Lexer {
    private:
        std::vector<Token*> tokens;
        std::vector<Automaton*> automata;

        int removeWhiteSpace(std::string& inputString);
        std::string& leadTrim(std::string& input, const std::string& toRemove);       
        std::string& trailTrim(std::string& input, const std::string& toRemove);
        std::string& trim(std::string& input, const std::string& toRemove);

    public:
        Lexer() {
            tokens = std::vector<Token*>();
            automata = std::vector<Automaton*>();

            automata.push_back(new MatcherAutomaton(",", COMMA));
            automata.push_back(new MatcherAutomaton(".", PERIOD));
            automata.push_back(new MatcherAutomaton("?", Q_MARK));
            automata.push_back(new MatcherAutomaton("(", LEFT_PAREN));
            automata.push_back(new MatcherAutomaton(")", RIGHT_PAREN));
            automata.push_back(new MatcherAutomaton(":", COLON));
            automata.push_back(new MatcherAutomaton(":-", COLON_DASH));
            automata.push_back(new MatcherAutomaton("*", MULTIPLY));
            automata.push_back(new MatcherAutomaton("+", ADD));
            automata.push_back(new MatcherAutomaton("Schemes", SCHEMES));
            automata.push_back(new MatcherAutomaton("Facts", FACTS));
            automata.push_back(new MatcherAutomaton("Rules", RULES));
            automata.push_back(new MatcherAutomaton("Queries", QUERIES));
            automata.push_back(new StringAutomaton(STRING));
            automata.push_back(new CommentAutomaton(COMMENT));
            automata.push_back(new BadComment(UNDEFINED));
            automata.push_back(new BadString(UNDEFINED));
            automata.push_back(new IdAutomaton(ID));

        };

        ~Lexer() {
            
            while(!tokens.empty()) {
                Token* d = tokens.back();
                tokens.pop_back();
                delete d;
            }
            
            while(!automata.empty()) {
                Automaton* d = automata.back();
                automata.pop_back();
                delete d;
            }
        }

        
        void Run(std::string& inputString);

        std::string toString();
        std::vector<Token*> const getTokens() { return tokens; };
};