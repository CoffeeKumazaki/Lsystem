#pragma once
#include <string>
#include <vector>
#include <map>

using Rule = std::pair<std::string, std::string>;
using Rules = std::map<std::string, std::string>;

/*
  rule: A => A+B(0.7), A-B(0.3)
*/
Rule string_to_rule(std::string srule);
std::string removeSpace(std::string trg);
