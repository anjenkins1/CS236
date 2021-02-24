#include "Parser.h"

void Parser::parse() {


    try {
        parseSCHEMES();
        parseDatalogProgram();
        isValid = true;
        toString();
    }
    catch (Token* e) {
        if (tokens.empty()) {

        }
        isValid = false;
        toString();
    }
};

void Parser::parseDatalogProgram() {
    // scheme schemeList FACTS COLON factList RULES COLON ruleList QUERIES COLON query queryList EOF

    parseCOLON();
    parseScheme();
    parseSchemeList();
    parseFACTS();
    parseCOLON();
    parseFactList();
    parseRULES();
    parseCOLON();
    parseRuleList();
    parseQUERIES();
    parseCOLON();
    parseQuery();
    parseQuerieList();
    parseEND_OF_FILE();
    return;

    
};

void Parser::parseRuleList() {
    if (tokens.at(tokenCount)->getTokenType() == ID) {
        parseRule();
    }
    else if (tokens.at(tokenCount)->getTokenType() == QUERIES) {
        return;
    }
    else {
        throw tokens.at(tokenCount);
    }
    parseRuleList();
};

void Parser::parseSchemeList() {

    if (tokens.at(tokenCount)->getTokenType() == ID) {
        parseScheme();
    }
    else if (tokens.at(tokenCount)->getTokenType() == FACTS) {
        return;
    }
    else {
        throw tokens.at(tokenCount);
    }
    parseSchemeList();
};

void Parser::parseQuerieList() {
    if (tokens.at(tokenCount)->getTokenType() == ID) {
        parseQuery();
    }
    else if (tokens.at(tokenCount)->getTokenType() == END_OF_FILE) {
        return;
    }
    else {
        throw tokens.at(tokenCount);
    }
    parseQuerieList();
};

void Parser::parseFactList() {
    if (tokens.at(tokenCount)->getTokenType() == ID) {
        parseFact();
    }
    else {
        return;
    }
    parseFactList();
};

void Parser::parseScheme() {

    parseID();

    tokenCount--;
    Predicate* newScheme = new Predicate(tokens.at(tokenCount)->getTokenStr());
    datalog.addScheme(newScheme);
    tokenCount++;

    parseLEFT_PAREN();
    parseID();

    tokenCount--;
    PlainParameter* newParameter = new PlainParameter(tokens.at(tokenCount)->getTokenStr());
    newScheme->addParameter(newParameter);
    tokenCount++;

    parseIdList(newScheme);

/*
    std::vector<PlainParameter *> parameterList = parseIdList();

   if (!parameterList.empty()) {
       for (int i = 0; i < (int)parameterList.size(); i++) {
           newScheme->addParameter(parameterList.at(i));
     }
  }
*/
    parseRIGHT_PAREN();
    return;
   
};

void Parser::parseFact() {

    parseID();

    tokenCount--;
    Predicate* newFact = new Predicate(tokens.at(tokenCount)->getTokenStr());
    datalog.addFact(newFact);
    tokenCount++;

    parseLEFT_PAREN();
    parseSTRING();

    tokenCount--;
    PlainParameter* newParameter = new PlainParameter(tokens.at(tokenCount)->getTokenStr());
    newFact->addParameter(newParameter);
    tokenCount++;

    parseStringList(newFact);
    parseRIGHT_PAREN();
    parsePERIOD();
    return;

};

void Parser::parseRule() {

    Rule* newRule = new Rule();
    parseHeadPredicate(newRule);
    parseCOLON_DASH();
    parsePredicate(newRule);
    parsePredicateList(newRule);
    parsePERIOD();
    datalog.addRule(newRule);
    return;


};

void Parser::parseQuery() {

    parsePredicate();
    parseQ_MARK();
};

void Parser::parseHeadPredicate(Rule* newRule) {
    parseID();

    tokenCount--;
    Predicate* newHeadPred = new Predicate(tokens.at(tokenCount)->getTokenStr());
    newRule->setHeadPredicate(newHeadPred);
    tokenCount++;

    parseLEFT_PAREN();
    parseID();

    tokenCount--;
    PlainParameter* newParameter = new PlainParameter(tokens.at(tokenCount)->getTokenStr());
    newHeadPred->addParameter(newParameter);
    tokenCount++;

    parseIdList(newHeadPred);
    parseRIGHT_PAREN();
    return;

};

void Parser::parsePredicate(){

    parseID();

    tokenCount--;
    Predicate* newPred = new Predicate(tokens.at(tokenCount)->getTokenStr());
    tokenCount++;

    parseLEFT_PAREN();

    newPred->addParameter(parseParameter());

    parseParameterList(newPred);

    parseRIGHT_PAREN();

    datalog.addQuery(newPred);
};

void Parser::parsePredicate(Rule* newRule) {

    parseID();

    tokenCount--;
    Predicate* newPred = new Predicate(tokens.at(tokenCount)->getTokenStr());
    tokenCount++;

    parseLEFT_PAREN();
    
    newPred->addParameter(parseParameter());

    parseParameterList(newPred);

    parseRIGHT_PAREN();

    newRule->addPredicate(newPred);

    return;

    /*
        if (tokens.at(tokenCount)->getTokenType() == ID) {
        tokenCount++;

        if (tokens.at(tokenCount)->getTokenType() == LEFT_PAREN) {
            tokenCount++;

                parseParameter();
                parseParameterList();

                if (tokens.at(tokenCount)->getTokenType() == RIGHT_PAREN) {
                    tokenCount++;
                    return;
                }

        }
    }
    */
};

void Parser::parsePredicateList(Rule* rule) {
    if (tokens.at(tokenCount)->getTokenType() == COMMA) {
        tokenCount++;
        parsePredicate(rule);
    }
    else if (tokens.at(tokenCount)->getTokenType() == PERIOD) {
        return;
    }
    else {
        throw tokens.at(tokenCount);
    }
    parsePredicateList(rule);
};

void Parser::parseParameterList(Predicate* pred) {
    if (tokens.at(tokenCount)->getTokenType() == COMMA) {
        tokenCount++;
        pred->addParameter(parseParameter());
    }
    else if (tokens.at(tokenCount)->getTokenType() == RIGHT_PAREN) {
        return;
    }
    else {
        throw tokens.at(tokenCount);
    }
    parseParameterList(pred);
};

void Parser::parseStringList(Predicate* newFact) {
    if (tokens.at(tokenCount)->getTokenType() == COMMA) {
        tokenCount++;

        if (tokens.at(tokenCount)->getTokenType() == STRING) {

            PlainParameter* newParameter = new PlainParameter(tokens.at(tokenCount)->getTokenStr());
            newFact->addParameter(newParameter);
            tokenCount++;
            parseStringList(newFact);
        }
    else if (tokens.at(tokenCount)->getTokenType() == RIGHT_PAREN) {
        return;
    }
    else {
        throw tokens.at(tokenCount);
        }
    }
}

void Parser::parseIdList(Predicate* pred) {

    if (tokens.at(tokenCount)->getTokenType() == COMMA) {
        tokenCount++;

    if (tokens.at(tokenCount)->getTokenType() == ID) {

            PlainParameter* newparam = new PlainParameter(tokens.at(tokenCount)->getTokenStr());
            pred->addParameter(newparam);

            tokenCount++;

            parseIdList(pred);
        } 
        else {
            throw tokens.at(tokenCount);
        }
    } 
    return;
}

std::vector<PlainParameter *> Parser::parseIdList() {
    //COMMA ID idList | lambda

    std::vector<PlainParameter *> parameters;

    if (tokens.at(tokenCount)->getTokenType() == COMMA) {
        tokenCount++;

        if (tokens.at(tokenCount)->getTokenType() == ID) {

            PlainParameter* newparam = new PlainParameter(tokens.at(tokenCount)->getTokenStr());
            parameters.push_back(newparam);

            tokenCount++;

            parameters = parseIdList();
        } 
        else {
            throw tokens.at(tokenCount);
        }
    } 
    return parameters;
};


Parameter* Parser::parseParameter() {

    if (tokens.at(tokenCount)->getTokenType() == STRING || tokens.at(tokenCount)->getTokenType() == ID) {

        PlainParameter* plain = new PlainParameter(tokens.at(tokenCount)->getTokenStr());
        tokenCount++;
        return plain;

    }

    else if (tokens.at(tokenCount)->getTokenType() == LEFT_PAREN) {
        tokenCount++;
        return parseExpression();
    }

    else {
        throw tokens.at(tokenCount);
    }
};

Expression* Parser::parseExpression() {

    Expression* express = new Expression();

    express->setParaOne(parseParameter());
    
    parseOperator();

    tokenCount--;
    express->setOp(tokens.at(tokenCount)->getTokenStr());
    tokenCount++;

    express->setParaTwo(parseParameter());

    parseRIGHT_PAREN();

    return express;
};

void Parser::parseOperator() {
    if (tokens.at(tokenCount)->getTokenType() == ADD || tokens.at(tokenCount)->getTokenType() == MULTIPLY) {
        tokenCount++;
        return;
    }
    else {
        throw tokens.at(tokenCount);
    }
};


//Base parsing

void Parser::parseCOMMA() {
    if (tokens.at(tokenCount)->getTokenType() == COMMA) {
        tokenCount++;
        return;
    }
    else {
        throw tokens.at(tokenCount);
    }
};

void Parser::parsePERIOD() {
    if (tokens.at(tokenCount)->getTokenType() == PERIOD) {
        tokenCount++;
        return;
    }
    else {
        throw tokens.at(tokenCount);
    }
};

void Parser::parseQ_MARK() {
    if (tokens.at(tokenCount)->getTokenType() == Q_MARK) {
        tokenCount++;
        return;
    }
    else {
        throw tokens.at(tokenCount);
    }   
};

void Parser::parseLEFT_PAREN() {
    if (tokens.at(tokenCount)->getTokenType() == LEFT_PAREN) {
        tokenCount++;
        return;
    }
    else {
        throw tokens.at(tokenCount);
    }   
};

void Parser::parseRIGHT_PAREN() {
    if (tokens.at(tokenCount)->getTokenType() == RIGHT_PAREN) {
        tokenCount++;
        return;
    }
    else {
        throw tokens.at(tokenCount);
    }   
}; 

void Parser::parseCOLON() {
    if (tokens.at(tokenCount)->getTokenType() == COLON) {
        tokenCount++;
        return;
    }
    else {
        throw tokens.at(tokenCount);
    }
}; 

void Parser::parseCOLON_DASH() {
    if (tokens.at(tokenCount)->getTokenType() == COLON_DASH) {
        tokenCount++;
        return;
    }
    else {
        throw tokens.at(tokenCount);
    }   
};

void Parser::parseMULTIPLY() {
    if (tokens.at(tokenCount)->getTokenType() == MULTIPLY) {
        tokenCount++;
        return;
    }
    else {
        throw tokens.at(tokenCount);
    }
};

void Parser::parseADD() {
    if (tokens.at(tokenCount)->getTokenType() == ADD) {
        tokenCount++;
        return;
    }
    else {
        throw tokens.at(tokenCount);
    }
};

void Parser::parseSCHEMES() {
    if (tokens.at(tokenCount)->getTokenType() == SCHEMES) {
        tokenCount++;
        return;
    }
    else {
        throw tokens.at(tokenCount);
    }
};

void Parser::parseFACTS() {
    if (tokens.at(tokenCount)->getTokenType() == FACTS) {
        tokenCount++;
        return;
    }
    else {
        throw tokens.at(tokenCount);
    }
};

void Parser::parseRULES() {
    if (tokens.at(tokenCount)->getTokenType() == RULES) {
        tokenCount++;
        return;
    }
    else {
        throw tokens.at(tokenCount);
    }
}; 

void Parser::parseQUERIES() {
    if (tokens.at(tokenCount)->getTokenType() == QUERIES) {
        tokenCount++;
        return;
    }
    else {
        throw tokens.at(tokenCount);
    }
}; 

void Parser::parseSTRING() {
    if (tokens.at(tokenCount)->getTokenType() == STRING) {
        tokenCount++;
        return;
    }
    else {
        throw tokens.at(tokenCount);
    }
};

void Parser::parseEND_OF_FILE() {
    if (tokens.at(tokenCount)->getTokenType() == END_OF_FILE) {
        tokenCount++;
        return;
    }
    else {
        throw tokens.at(tokenCount);
    }
};

void Parser::parseID() {
    if (tokens.at(tokenCount)->getTokenType() == ID) {
        tokenCount++;
        return;
    }
    else {
        throw tokens.at(tokenCount);
    }
}; 

std::string Parser::toString() {
    if (isValid) {
        std::cout << "Success!" << std::endl;
        std::cout << datalog.toString();
        return "Success!" + datalog.toString();
    }
    else {
        std::cout << "Failure!" << std::endl;
        if (!tokens.empty()) {
            std::cout << "  " << tokens.at(tokenCount)->toString() << std::endl;
        }
        else {
            std::cout << "EMPTY" << std::endl;
        }
        return "Failure!";
    }
}