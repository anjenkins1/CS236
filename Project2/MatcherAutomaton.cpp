#include "MatcherAutomaton.h"

int MatcherAutomaton::Start(const std::string& input) {

    newLines = 0;
    isValid = true;
    bool isMatch = true;
    inputRead = 0; // member variable inherited from Automaton class
    for (int i = 0; i < (int)toMatch.size() && isMatch; i++) {
        if (input[i] != toMatch[i]) {
            isMatch = false;
        }
        if (input[i] == '\n') {
            newLines++;
        }     
    }
    if (isMatch) {
        inputRead = toMatch.size();
    }
    return inputRead;
}