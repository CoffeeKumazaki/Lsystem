#pragma once

struct LSystemOption {

  std::string name;
  std::string init;
  std::vector<std::string> rules;
  std::vector<char> constants;

  double angle; // [deg]
  int iteration;
};

LSystemOption getDefaultSystemOption();
LSystemOption readSystemOption(std::string filepath);