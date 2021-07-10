#pragma once
#include <string>
#include <vector>
#include <map>

using StocasticRule = std::pair<std::string /* rule */, float/* probability */>;
using StocasticRules = std::vector<StocasticRule>;

class Rule {
  
public:
  Rule();
  Rule(std::string srule);
  std::string convert();

  void print();

private:
  void parse_rule(std::string srule);

public:
  std::string pre;
  StocasticRules rules;
  float prob_tot = 0.0;
};

using Rules = std::map<std::string /* target */, Rule>;