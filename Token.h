#pragma once
#include <iostream>
#include <string>

enum TokenType {COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH,
                MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, STRING, COMMENT, UNDEFINED, END_OF_FILE, ID};

class Token {
    public:
        Token();
        Token(std::string tkStr, int lNum, TokenType t)
        {
            tokenStr = tkStr;
            lineNum = lNum;
            type = t;
        };
        ~Token() = default;

        std::string toString();

    private:
        std::string tokenStr;
        int lineNum;
        TokenType type;

        std::string tokenToString(TokenType type);

};