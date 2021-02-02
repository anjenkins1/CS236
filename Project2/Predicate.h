#pragma once
#include <string>
#include <vector>
#include "Parameter.h"

class Predicate {
    private:
    std::string id;
    std::vector<Parameter> parameters;

    public:
    Predicate() {};
    Predicate(std::string id) {
        this->id = id;
    }

    void addParameter (Parameter parameter) {
        parameters.push_back(parameter);
    }

    std::string const getId () {
        return id;
    }

    std::string toString() {
        std::string toReturn;

        toReturn += "( ";
        for (int i = 0; i < (int) parameters.size() - 1; i++) {
            toReturn += (parameters.at(i).toString() + ", ");
        }

        toReturn += ((parameters.at(parameters.size()-1).toString()) + " )");
        return toReturn;
    }
};