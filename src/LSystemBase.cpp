#include <stdafx.hpp>
#include <LSystemBase.hpp>

LSystemBase::LSystemBase(std::string _variable)
 : variable(_variable) 
{
}

LSystemBase::LSystemBase(std::string _variable, VS _rules)
 : LSystemBase(_variable)
{
  for (size_t i = 0; i < _rules.size(); i++) {
    add_rule(_rules[i]);
  }
}

LSystemBase::LSystemBase(std::string _variable, Rules _rules)
 : LSystemBase(_variable)
{
  rules = _rules;
};

LSystemBase::~LSystemBase() {

}

void LSystemBase::add_rule(Rule rule) {
  rules[rule.pre] = rule;
}

void LSystemBase::add_rule(std::string srule) {
  try
  {
    Rule r(srule);
    add_rule(r);
  }
  catch(...)
  {
    std::cerr << "skip " << srule << '\n';
  }
  
}

void LSystemBase::iterate(int n /*=1*/) {

  for (size_t itr = 0; itr < n; itr++) {

    std::string new_v = "";
    for (size_t i = 0; i < variable.size(); i++) {
      std::string key;
      key += variable[i];
      if (rules.count(key) > 0) {
        new_v += rules[key].convert();
      }
      else {
        new_v += key;
      }
    }
    variable = new_v;
  }

}
