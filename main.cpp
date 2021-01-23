#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Project 1/Lexer.h"
#include "Project 1/Token.h"

int main (int argc, char* argv[]) {
    
    //Take in input file from argument passed into main
    std::string inputFile = argv[1];

    //Declare input file stream and pass input file
    std::ifstream ifs(inputFile);

    /*
    Open the input file using the file stream and then pass the
    contents of the file into a string called "inputString"
    */

    std::string inputString;
    inputString.assign( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );


    Lexer *trial = new Lexer;
    trial->Run(inputString);

    return 0;
}