#pragma once
#include "Parameter.h"

class Expression : public Parameter {

    private:
    Parameter* paraOne;
    Parameter* paraTwo;
    std::string op;

    public:
    
    Expression() {};
    Expression(Parameter* p1, Parameter* p2, std::string o) {
        paraOne = p1;
        paraTwo = p2;
        op = o;
    };

    void setParaOne(Parameter* paraOne) {
        this->paraOne = paraOne;
    }

    void setParaTwo(Parameter* paraTwo) {
        this->paraTwo = paraTwo;
    }

    void setOp(std::string op) {
        this->op = op;
    }

    std::string toString() {
        return "(" + paraOne->toString() + op + paraTwo->toString() + ")";
    }
};