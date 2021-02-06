#pragma once
#include <string>
#include <vector>
#include "Predicate.h"

class Rule {
    private:
    std::vector<Predicate*> predicates;
    Predicate* headPredicate;

    public:

    Rule() {};
    Rule(Predicate* headPredicate) { this->headPredicate = headPredicate; };

    void addPredicate (Predicate* pred) {
        predicates.push_back(pred);
    }

    void setHeadPredicate (Predicate* pred) {
        headPredicate = pred;
    }

    std::string toString() {
        std::string toReturn;

        toReturn += (headPredicate->toString() + " := ");

        if (!predicates.empty()) {
            for (int i = 0; i < (int) predicates.size() - 1; i++) {
                toReturn += (predicates.at(i)->toString() + ",");
            }
            toReturn += ((predicates.at(predicates.size()-1)->toString()) + ".");
        }

        return toReturn;
    }
};