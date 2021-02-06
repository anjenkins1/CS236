#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <sstream>
#include "Predicate.h"
#include "Parameter.h"
#include "PlainParameter.h"
#include "Expression.h"
#include "Rule.h"

class DatalogProgram {

    private:
        std::vector<Predicate*> schemes;
        std::vector<Predicate*> facts;
        std::vector<Predicate*> queries;
        std::vector<Rule*> rules;
        std::set<std::string> domain;

    public:
       DatalogProgram() {

       }
      //  ~DatalogProgram();

      void addScheme(Predicate* scheme) {
          schemes.push_back(scheme);
      }

      void addFact(Predicate* fact) {
          facts.push_back(fact);
      }

      void addQuery(Predicate* query) {
          queries.push_back(query);
      }
      
      void addRule(Rule* rule) {
          rules.push_back(rule);
      }

        std::string toString() {
            std::stringstream ss;

            int schemeSize = 0;
            int factSize = 0;
            int querySize = 0;
            int ruleSize = 0;

            if (!schemes.empty()) {
                schemeSize = (int)schemes.size();
            }

            if (!facts.empty()) {
                factSize = (int)facts.size();
            }

            if (!queries.empty()) {
                querySize = (int)queries.size();
            }

            if (!rules.empty()) {
                ruleSize = (int)rules.size();
            }
            

            ss << "Schemes(" << schemeSize << "):" << std::endl;

            for (int i = 0; i < schemeSize; i++) {
                ss << '\t' << schemes.at(i)->toString() << std::endl;
            }

            ss << "Facts(" << factSize << "):" << std::endl;

            for (int i = 0; i < factSize; i++) {
                ss << '\t' << facts.at(i)->toString() << "." << std::endl;

                for (int j=0; j < (int)facts.at(i)->getParameters().size(); j++) {
                    domain.insert(facts.at(i)->getParameters().at(j)->toString());
                }
                
            }

            ss << "Rules(" << ruleSize << "):" << std::endl;

            for (int i = 0; i < ruleSize; i++) {
                ss << '\t' << rules.at(i)->toString() << std::endl;
            }

            ss << "Queries(" << querySize << "):" << std::endl;

            for (int i = 0; i < querySize; i++) {
                ss << '\t' << queries.at(i)->toString() << "?" << std::endl;
            }
            
            if (factSize > 0) {
                ss << "Domain(" << factSize << "):" << std::endl;

                for (auto elem : domain) {
                    ss << elem << std::endl;
                }
            }
            else {
                ss << "Domain(" << factSize << "):" << std::endl;
            }
            

            return ss.str();
        }

};