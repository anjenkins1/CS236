#pragma once
#include "Parameter.h"

class Expression : public Parameter {

    Parameter paraOne;
    Parameter paraTwo;
    std::string op;

    Expression(Parameter p1, Parameter p2, std::string o) {
        paraOne = p1;
        paraTwo = p2;
        op = o;
    };

    std::string toString() {
        return "( " + paraOne.toString() + " " + op + " " + paraTwo.toString() + " )";
    }
};