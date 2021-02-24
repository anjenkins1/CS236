#include "IdAutomaton.h"

int IdAutomaton::Start(const std::string& input) {
    inputRead = 0;
    int charCount = 0;

    if (isalpha(input[charCount])) {
        while (charCount < (int)input.length()) {
            if (!isalpha(input[charCount]) && !isdigit(input[charCount])) {
                break;
            }
            charCount++;
        }

        if (input.substr(0,charCount) == "Rules" ||
            input.substr(0,charCount) == "Facts" ||
            input.substr(0,charCount) == "Queries" ||
            input.substr(0,charCount) == "Schemes" ) {
                return inputRead;
            }
            
        inputRead = charCount;
        return inputRead;
    }

    return inputRead;
}