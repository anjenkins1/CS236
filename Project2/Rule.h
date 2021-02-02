#pragma once
#include <string>
#include <vector>
#include "Predicate.h"

class Rule {
    private:
    std::vector<Predicate> predicates;
    Predicate headPredicate;

    public:

    Rule(Predicate headPredicate) { this->headPredicate = headPredicate; };

    void addPredicate (Predicate pred) {
        predicates.push_back(pred);
    }

    std::string toString() {
        std::string toReturn;

        toReturn += (headPredicate.toString() + " := ");
        for (int i = 0; i < (int) predicates.size() - 1; i++) {
            toReturn += (predicates.at(i).toString() + ", ");
        }

        toReturn += ((predicates.at(predicates.size()-1).toString()) + ".");
        return toReturn;
    }
};