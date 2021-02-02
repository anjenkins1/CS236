#include "Parser.h"

void Parser::parse() {

    try {
        if (tokens.at(tokenCount)->getTokenType() == SCHEMES) {
            tokenCount++;
            parseDatalogProgram();
            isValid = true;
            toString();
        }
        else {
            throw tokens.at(tokenCount);
        }
    }
    catch (Token* e) {
        if (tokens.empty()) {

        }
        isValid = false;
        toString();
    }
}

void Parser::parseDatalogProgram() {
    // scheme schemeList FACTS COLON factList RULES COLON ruleList QUERIES COLON query queryList EOF

    if (tokens.at(tokenCount)->getTokenType() == COLON) {
        tokenCount++;

        parseScheme();
        parseSchemeList();

        if (tokens.at(tokenCount)->getTokenType() == FACTS) {
            tokenCount++;

            if(tokens.at(tokenCount)->getTokenType() == COLON) {
                tokenCount++;

                parseFactList();
                
                if (tokens.at(tokenCount)->getTokenType() == RULES) {
                    tokenCount++;

                    if (tokens.at(tokenCount)->getTokenType() == COLON) {
                        tokenCount++;

                        parseRuleList();

                        if (tokens.at(tokenCount)->getTokenType() == QUERIES) {
                            tokenCount++;

                                if (tokens.at(tokenCount)->getTokenType() == COLON) {
                                    tokenCount++;

                                    parseQuery();
                                    parseQuerieList();

                                    if (tokens.at(tokenCount)->getTokenType() == END_OF_FILE) {
                                        return;
                                    }

                                    else {
                                        throw tokens.at(tokenCount);
                                    }
                                }

                                else {
                                    throw tokens.at(tokenCount);
                                }
                            }

                            else {
                                throw tokens.at(tokenCount);
                            }
                        }
                    }
                    else {
                        throw tokens.at(tokenCount);
                    }
                }
                else {
                    throw tokens.at(tokenCount);
                }
            }
            else {
                throw tokens.at(tokenCount);
            }
        
        }
        else {
            throw tokens.at(tokenCount);
        }
}

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
    if (tokens.at(tokenCount)->getTokenType() == ID) {
        tokenCount++;

        if (tokens.at(tokenCount)->getTokenType() == LEFT_PAREN) {
            tokenCount++;

            if (tokens.at(tokenCount)->getTokenType() == ID) {
                tokenCount++;
                parseIdList();
                
                if (tokens.at(tokenCount)->getTokenType() == RIGHT_PAREN) {
                    tokenCount++;
                    return;
                }
                else {
            throw tokens.at(tokenCount);
        }
            }
            else {
            throw tokens.at(tokenCount);
        }

        }
        else {
            throw tokens.at(tokenCount);
        }
    }
    else {
            throw tokens.at(tokenCount);
        }
};

void Parser::parseFact() {
    if (tokens.at(tokenCount)->getTokenType() == ID) {
        tokenCount++;

        if (tokens.at(tokenCount)->getTokenType() == LEFT_PAREN) {
            tokenCount++;

            if (tokens.at(tokenCount)->getTokenType() == STRING) {
                tokenCount++;
                parseStringList();
                
                if (tokens.at(tokenCount)->getTokenType() == RIGHT_PAREN) {
                    tokenCount++;
                }
                    if (tokens.at(tokenCount)->getTokenType() == PERIOD) {
                        tokenCount++;
                        return;
                    }
                    else {
            throw tokens.at(tokenCount);
        }
            }
            else {
            throw tokens.at(tokenCount);
        }

        }
        else {
            throw tokens.at(tokenCount);
        }
    }
    else {
            throw tokens.at(tokenCount);
        }
};

void Parser::parseRule() {
    parseHeadPredicate();
    if (tokens.at(tokenCount)->getTokenType() == COLON_DASH) {
        tokenCount++;
        parsePredicate();
        parsePredicateList();
        if (tokens.at(tokenCount)->getTokenType() == PERIOD) {
            tokenCount++;
            return;
        }
        else {
            throw tokens.at(tokenCount);
        }
    }
    else {
        throw tokens.at(tokenCount);
    }
};

void Parser::parseQuery() {
    parsePredicate();
    if (tokens.at(tokenCount)->getTokenType() == Q_MARK) {
        tokenCount++;
        return;
    }
    else {
        throw tokens.at(tokenCount);
    }
};

void Parser::parseHeadPredicate() {
    if (tokens.at(tokenCount)->getTokenType() == ID) {
        tokenCount++;

        if (tokens.at(tokenCount)->getTokenType() == LEFT_PAREN) {
            tokenCount++;

            if (tokens.at(tokenCount)->getTokenType() == ID) {
                tokenCount++;

                parseIdList();

                if (tokens.at(tokenCount)->getTokenType() == RIGHT_PAREN) {
                    tokenCount++;
                    return;
                }
            }

        }
    }
};

void Parser::parsePredicate() {
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
};

void Parser::parsePredicateList() {
    if (tokens.at(tokenCount)->getTokenType() == COMMA) {
        tokenCount++;
        parsePredicate();
    }
    else if (tokens.at(tokenCount)->getTokenType() == PERIOD) {
        return;
    }
    else {
        throw tokens.at(tokenCount);
    }
    parsePredicateList();
};

void Parser::parseParameterList() {
    if (tokens.at(tokenCount)->getTokenType() == COMMA) {
        tokenCount++;
        parseParameter();
    }
    else if (tokens.at(tokenCount)->getTokenType() == RIGHT_PAREN) {
        return;
    }
    else {
        throw tokens.at(tokenCount);
    }
    parseParameterList();
};

void Parser::parseStringList() {
    if (tokens.at(tokenCount)->getTokenType() == COMMA) {
        tokenCount++;

        if (tokens.at(tokenCount)->getTokenType() == STRING) {
            tokenCount++;
            parseStringList();
        }
    else if (tokens.at(tokenCount)->getTokenType() == RIGHT_PAREN) {
        return;
    }
    else {
        throw tokens.at(tokenCount);
        }
    }
}

void Parser::parseIdList() {
    //COMMA ID idList | lambda
    if (tokens.at(tokenCount)->getTokenType() == COMMA) {
        tokenCount++;

        if (tokens.at(tokenCount)->getTokenType() == ID) {
            tokenCount++;

            parseIdList();
        } 
        else {
            throw tokens.at(tokenCount);
        }
    } 
    return;
};

void Parser::parseParameter() {
    if (tokens.at(tokenCount)->getTokenType() == STRING || tokens.at(tokenCount)->getTokenType() == ID) {
        tokenCount++;
        return;
    }
    else if (tokens.at(tokenCount)->getTokenType() == LEFT_PAREN) {
        tokenCount++;
        parseExpression();
    }
    else {
        throw tokens.at(tokenCount);
    }
};

void Parser::parseExpression() {
    parseParameter();
    parseOperator();
    parseParameter();
    if (tokens.at(tokenCount)->getTokenType() == RIGHT_PAREN) {
        tokenCount++;
        return;
    }
    else {
        throw tokens.at(tokenCount);
    }
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

std::string Parser::toString() {
    if (isValid) {
        std::cout << "Success!" << std::endl;
        return "Success!";
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