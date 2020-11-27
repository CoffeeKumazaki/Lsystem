#include <Rule.hpp>

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

  srule = removeSpace(srule);
  auto pos = srule.find("=>");
  if (pos == -1){
    throw "Rule should include =>";
  }
  return std::make_pair(srule.substr(0, pos), srule.substr(pos+2));
}