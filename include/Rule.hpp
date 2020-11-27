#pragma once
#include <string>
#include <vector>

struct Rule {
  std::string trg;
  std::string rule;

  void print() {
    std::cout << "target: " << trg << std::endl;
    std::cout << "rule  : " << rule << std::endl;
  }
};


std::string removeSpace(std::string trg) {

  std::string ret;
  for (size_t i = 0; i < trg.size(); i++)
  {
    if (trg[i] != ' ') {
      ret += trg[i];
    }
  }

  return ret;
}
/*
  rule: A => A+B(0.7), A-B(0.3)
*/
Rule string_to_rule(std::string srule) {

  Rule r;
  srule = removeSpace(srule);
  auto pos = srule.find("=>");
  if (pos != -1){
    r.trg = srule.substr(0, pos);
    r.rule = srule.substr(pos+2);
  }
  return r;
}

using VRule = std::vector<Rule>;
using VRule_IT = std::vector<Rule>::iterator;