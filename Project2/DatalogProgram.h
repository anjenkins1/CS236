#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <sstream>
#include "Predicate.h"
#include "Rule.h"

class DatalogProgram {

    private:
        std::vector<Predicate> schemes;
        std::vector<Predicate> facts;
        std::vector<Predicate> queries;
        std::vector<Rule> rules;
        std::set<std::string> domain;

    public:
        DatalogProgram();
        ~DatalogProgram();

        std::string toString() {
            std::stringstream ss;

            ss << "Schemes(" << schemes.size() << "):" << std::endl;

            for (int i = 0; i < schemes.size(); i++) {
                ss << schemes.at(i).toString() << std::endl;
            }

            ss << "Facts(" << facts.size() << "):" << std::endl;

            for (int i = 0; i < facts.size(); i++) {
                ss << facts.at(i).toString() << std::endl;
                domain.insert(facts.at(i).getId());
            }

            ss << "Rules(" << rules.size() << "):" << std::endl;

            for (int i = 0; i < rules.size(); i++) {
                ss << rules.at(i).toString() << std::endl;
            }

            ss << "Queries(" << queries.size() << "):" << std::endl;

            for (int i = 0; i < queries.size(); i++) {
                ss << queries.at(i).toString() << std::endl;
            }
            
            ss << "Domain(" << domain.size() << "):" << std::endl;

            for (auto elem : domain) {
                ss << elem << std::endl;
            }

        }

};