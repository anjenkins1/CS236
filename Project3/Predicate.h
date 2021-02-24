#pragma once
#include <string>
#include <vector>
#include "Parameter.h"

class Predicate {
    private:
    std::string id;
    std::vector<Parameter*> parameters;

    public:
    Predicate() {};
    Predicate(std::string id) {
        this->id = id;
    }

    ~Predicate() {
        if (!parameters.empty()) {
            for (int i = 0; i < (int)parameters.size(); i++) {
                delete parameters.at(i);
            }
        }
    }

    void addParameter (Parameter* parameter) {
        parameters.push_back(parameter);
    }

    std::vector<Parameter*> getParameters() {
        return parameters;
    }

    std::string const getId () {
        return id;
    }

    std::string toString() {
        std::string toReturn;

        toReturn+=id;

        if (!parameters.empty()) {
            toReturn += "(";
            for (int i = 0; i < (int) parameters.size()-1; i++) {
            toReturn += (parameters.at(i)->toString() + ",");
            }
            toReturn += ((parameters.at(parameters.size()-1)->toString()) + ")");
        }

        
        return toReturn;
    }
};