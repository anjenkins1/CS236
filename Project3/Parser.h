#pragma once
#include <iostream>
#include <vector>
#include "Token.h"
#include "DatalogProgram.h"
#include "Parameter.h"
#include "PlainParameter.h"
#include "Expression.h"

class Parser {

    public:
        Parser(std::vector<Token*> tokens) {
            this->tokens = tokens; 
            this->isValid = false;
            this->tokenCount = 0;
        };

        void parse();

        std::string toString();

    private:
        bool isValid;
        int tokenCount;
        std::vector<Token*> tokens;
        DatalogProgram datalog;

        void parseDatalogProgram();

        void parseRuleList();
        void parseSchemeList();
        void parseQuerieList();
        void parseFactList();

        void parseScheme();
        void parseFact();
        void parseRule();
        void parseQuery();

        void parseHeadPredicate(Rule* rule);
        void parsePredicate(Rule* rule);
        void parsePredicate();

        void parsePredicateList(Rule* rule);
        void parseParameterList(Predicate* pred);
        void parseStringList(Predicate* newFact);
        std::vector<PlainParameter *> parseIdList();
        void parseIdList(Predicate* pred);

        Parameter* parseParameter();
        Expression* parseExpression();
        void parseOperator();

        void parseCOMMA();
        void parsePERIOD();
        void parseQ_MARK();
        void parseLEFT_PAREN();
        void parseRIGHT_PAREN(); 
        void parseCOLON(); 
        void parseCOLON_DASH();
        void parseMULTIPLY();
        void parseADD();
        void parseSCHEMES();
        void parseFACTS();
        void parseRULES(); 
        void parseQUERIES(); 
        void parseSTRING();
        void parseEND_OF_FILE();
        void parseID();     

};