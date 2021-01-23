#include "Project 1/Lexer.h"

std::string removeWhiteSpace(std::string inputString)
{
    if (inputString != "") {
        int spaceCount = 0;
        while (isspace(inputString.at(spaceCount))) {
            spaceCount++;
        }
        inputString.erase(0,spaceCount);
    }

    return inputString;
}

void Lexer::Run(std::string inputString) 
{
    int lineNumber = 1;

    while (inputString.size() > 0) {
        int maxRead = 0;
        Automaton *maxAutomaton = automata[0];

        inputString = removeWhiteSpace(inputString);

    }

    std::cout << inputString << std::endl;
}