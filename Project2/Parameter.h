#pragma once
#include <string>

class Parameter {
    protected:
    std::string parameter;

    public:

    Parameter() {};

    virtual ~Parameter() = default;

    virtual std::string toString() {return " ";};

};