#pragma once
#include <string>

class Parameter {
    protected:
    std::string parameter;

    public:
    Parameter() {};

    virtual std::string toString();
};