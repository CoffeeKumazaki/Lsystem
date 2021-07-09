#pragma once

struct LSystemOption {

  std::string name;
  std::string init;
  std::vector<std::string> rules;
  std::vector<char> constants;

  double step  = 1.0;
  double angle = 90; // [deg]
  int iteration = 5;
};

LSystemOption getDefaultSystemOption();
LSystemOption readSystemOption(std::string filepath);