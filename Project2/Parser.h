#pragma once
#include <iostream>
#include <vector>
#include "Token.h"

class Parser {

    public:
        Parser(std::vector<Token*> tokens) {
            this->tokens = tokens; 
            this->isValid = false;
            this->tokenCount = 0;
        };
    //    ~Parser();

        void parse();

        std::string toString();

    private:
        bool isValid;
        int tokenCount;
        std::vector<Token*> tokens;

        void parseDatalogProgram();

        void parseRuleList();
        void parseSchemeList();
        void parseQuerieList();
        void parseFactList();

        void parseScheme();
        void parseFact();
        void parseRule();
        void parseQuery();

        void parseHeadPredicate();
        void parsePredicate();

        void parsePredicateList();
        void parseParameterList();
        void parseStringList();
        void parseIdList();

        void parseParameter();
        void parseExpression();
        void parseOperator();


};