#pragma once
#include "Rule.hpp"

class LSystemBase {
public:
	LSystemBase(std::string _variable) : variable(_variable) {}
	LSystemBase(std::string _variable, VS _rules) : LSystemBase(_variable) {

    for (size_t i = 0; i < _rules.size(); i++) {
      add_rule(string_to_rule(_rules[i]));
    }
  }
	LSystemBase(std::string _variable, VRule _rules) : LSystemBase(_variable)
  {
    rules.assign(_rules.begin(), _rules.end());
  };
  ~LSystemBase(){};

  void add_rule(Rule rule) {
    rules.emplace_back(rule);
  }
  void add_rule(std::string srule) {
    add_rule(string_to_rule(srule));
  }

  void iterate(int n = 1);
  std::string get_condition() { return variable; }

  void show_rules() {
    for (auto r : rules) {
      r.print();
    }
  }

private:
  std::string variable;
  VRule rules;
};