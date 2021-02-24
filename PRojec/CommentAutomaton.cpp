#include "CommentAutomaton.h"

int CommentAutomaton::Start(const std::string& input) {
    inputRead = 0;
    newLines = 0;
    int charCount = 0;

    isValid = true;

    if (input[charCount] == '#') {
        charCount++;

        //Blank comment (just '#')
        if (charCount == (int)input.length()) {
            inputRead = charCount;
            isValid = true;
            return inputRead;
        }

        //Block comment ('#|')
        else if (input[charCount] == '|') {
            charCount++;
            while(charCount < (int)input.length()) {
                if (input[charCount] == '\n') {
                    newLines++;
                }
                else if (input[charCount] == '|') {
                    charCount++;
                    if (input[charCount] == '#') {
                        charCount++;
                        inputRead = charCount;
                        return inputRead;
                    }
                }
                charCount++;
            }
        }

        //Line comment continued
        else {
            while(charCount < (int)input.length()) {
                if (input[charCount] == '\n') {
                    inputRead = charCount;
                    return inputRead;
                }
                charCount++;
            }
        }
    }
    
    return inputRead;

}