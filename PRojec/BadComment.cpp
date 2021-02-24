#include "BadComment.h"

int BadComment::Start(const std::string& input) {
    inputRead = 0;
    newLines = 0;
    int charCount = 0;

    if (input[charCount] == '#') {
        charCount++;

        //Block comment ('#|')
        if (input[charCount] == '|') {
            charCount++;
            while(charCount < (int)input.length()) {
                if (input[charCount] == '\n') {
                    newLines++;
                }
                else if (input[charCount] == '|') {
                    charCount++;
                    if (input[charCount] == '#') {
                        return 0;
                    }
                }
                charCount++;
            }
            newLines++;
        }
    }
    
    inputRead = charCount;
    return inputRead;

}