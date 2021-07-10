#include <iostream>
#include <random>
#include <Rule.hpp>

using namespace std;

string removeSpace(string trg) {

  string ret;
  for (size_t i = 0; i < trg.size(); i++)
  {
    if (trg[i] != ' ') {
      ret += trg[i];
    }
  }

  return ret;
}

Rule::Rule() {
}

Rule::Rule(string srule) {

  srule = removeSpace(srule);
  auto pos = srule.find("=>");
  if (pos == -1){
    throw "Rule should include =>";
  }
  pre = srule.substr(0, pos);
  srule.erase(0, pos+2);

  while ((pos = srule.find(",")) != string::npos ) {
    string s = srule.substr(0, pos);
    parse_rule(s);
    srule.erase(0, pos + 1);
  }
  parse_rule(srule);
}

void Rule::parse_rule(string srule) {

  auto pos1 = srule.find("(");
  auto pos2 = srule.find(")");
  if (pos1 != -1 && pos2 != -1) {
    string r = srule.substr(0, pos1);
    float p = stof(srule.substr(pos1+2, pos2-pos1-2));
    // cout << r << " " << p << endl;
    rules.push_back(StocasticRule(r, p));
    prob_tot += p;
  }
  else if (pos1 == -1 && pos2 == -1) {
    // cout << srule << endl;
    float p = (prob_tot > 0) ? max(0.0, 1.0 - prob_tot) : 1.0;
    rules.push_back(StocasticRule(srule, p));
    prob_tot += p;
  }
  else {
    throw "( or ) is missing.";
  }
}

string Rule::convert() {

  random_device rd;
  default_random_engine eng(rd());
  uniform_real_distribution<float> distr(0.0, prob_tot);

  float p = distr(eng);
  float ptot = 0.0;
  for (auto r : rules) {
    if (r.second + ptot >= p) {
      return r.first;
    }
    ptot += r.second;
  }

  throw "error to convert";
}

void Rule::print() {
  cout << "--" << endl;
  cout << "  target : " + pre << endl;
  for (size_t i = 0; i < rules.size(); i++) {
    cout <<  ((i == 0) ? "  rule   : " : "           ") + rules[i].first 
         <<  " (" << rules[i].second << ")" << endl;
  }  
}