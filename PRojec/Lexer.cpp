#include "Lexer.h"

void Lexer::Run(std::string& inputString) 
{
    int lineNumber = 1;
    int totalLines = 1;

    for (int i = 0; i < (int)inputString.length(); i++) {
        if (inputString[i] == '\n') {
            totalLines++;
        }
    }

    if (totalLines == 1) {
        if (inputString.empty()) {
            Token *eofToken = new Token("", totalLines, END_OF_FILE);
            tokens.push_back(eofToken);
        }
    }
//    leadTrim(inputString, "\t\n\v\f\r ");

//    bool isValid = false;

    while (inputString.size() > 0 && totalLines != 1) {
        int maxRead = 0;
        int zeroCount = 0;
  //      bool noTokens = false;

        Automaton *maxAutomaton = automata[0];

       int lineCount = removeWhiteSpace(inputString);

      
        if (inputString.empty()) {
            Token *eofToken = new Token("", totalLines, END_OF_FILE);
            tokens.push_back(eofToken);
            break;
        }
        else {
            lineNumber += lineCount;
        }

        for(int i = 0; i < (int)automata.size(); i++) {

            int inputRead = automata.at(i)->Start(inputString);

            if (inputRead > maxRead) {
                maxRead = inputRead;
                maxAutomaton = automata.at(i);
                }
            else if (inputRead == 0) {
                zeroCount++;
            }
        }
/*
        if (zeroCount == (int)automata.size()) {
            noTokens = true;
        }
*/
        if (maxRead > 0) {
            Token *newToken = maxAutomaton->CreateToken(inputString.substr(0,maxRead),lineNumber);
            lineNumber += maxAutomaton->NewLinesRead();
            tokens.push_back(newToken);
        }

/*
        else if (noTokens) {
            maxRead = (int)inputString.length();
            Token *invalidToken = new Token(inputString, lineNumber, UNDEFINED);
            tokens.push_back(invalidToken);

            for (int i = 0; i < maxRead; i++) {
                if (inputString[i] == '\n') {
                    lineNumber += 1;
                }
            }
            lineNumber -= 1;
        }
*/
        else {
            maxRead = 1;
            Token *invalidToken = new Token(inputString.substr(0,1), lineNumber, UNDEFINED);
            tokens.push_back(invalidToken);
        }

        inputString.erase(0,maxRead);

        if (inputString.empty()) {
            Token *eofToken = new Token("", totalLines, END_OF_FILE);
            tokens.push_back(eofToken);
        }
    }
}

std::string Lexer::toString() {
    std::stringstream ss;
    int totalTokens = 0;
    
    for (int i = 0; i < (int)tokens.size(); i++) {
        ss << tokens.at(i)->toString() << "\n";
        totalTokens++;
    }
    ss << "Total Tokens = " << totalTokens;
    return ss.str();
}

int Lexer::removeWhiteSpace(std::string& inputString)
{
    int newLineCount = 0;
    int spaceCount = 0;
    while (isspace(inputString[spaceCount])) {
        if(inputString[spaceCount] == '\n') {
            newLineCount++;
        }
        spaceCount++;    
        }
        inputString.erase(0,spaceCount);
    
    return newLineCount;
}

std::string& Lexer::leadTrim(std::string& input, const std::string& toRemove) {
    input.erase(0, input.find_first_not_of(toRemove));
    return input;
}

std::string& Lexer::trailTrim(std::string& input, const std::string& toRemove) {
    input.erase(input.find_last_not_of(toRemove) + 1);
    return input;
}

std::string& Lexer::trim(std::string& input, const std::string& toRemove) {
    return leadTrim(trailTrim(input, toRemove), toRemove);
}