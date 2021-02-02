#include "StringAutomaton.h"

int StringAutomaton::Start(const std::string& input) {
    
    inputRead = 0;
    newLines = 0;

    if (input[0] == '\'') {
        bool stringClosed = false;
        int i = 1;
        int apostrapheCount = 1;

        while (!stringClosed && apostrapheCount % 2 != 0 && i < (int)input.length()) {
            if (input[i] == '\n') {
                newLines++;
            }
            if (input[i] == '\'') {
                apostrapheCount++;
                i++;
                if (input[i] != '\'') {
                    stringClosed = true;
                }
                else {
                apostrapheCount++;
                }
            }
            i++;
        }

        if (apostrapheCount % 2 == 0) {
            inputRead = i-1;
        }

    }

    return inputRead;
}