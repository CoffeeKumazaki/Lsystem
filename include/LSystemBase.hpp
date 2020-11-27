#pragma once
#include "Rule.hpp"

class LSystemBase {
public:
  LSystemBase(std::string _variable);
  LSystemBase(std::string _variable, VS _rules);
  LSystemBase(std::string _variable, Rules _rules);
  ~LSystemBase();

  void add_rule(Rule rule);
  void add_rule(std::string srule);

  void iterate(int n = 1);
  std::string get_condition() { return variable; }

  void show_rules() {
    std::cout << "[rules]" << std::endl;
    for (auto r : rules)
    {
      std::cout << " ---" << std::endl;
      std::cout << "  target: " << r.first << std::endl;
      std::cout << "  rule  : " << r.second << std::endl;
    }
  }

private:
  std::string variable;
  Rules rules;
};