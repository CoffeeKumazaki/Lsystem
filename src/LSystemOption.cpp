#include "stdafx.hpp"
#include "LSystemOption.hpp"
#include <ryml.hpp>

LSystemOption getDefaultSystemOption() {
  LSystemOption defaultOption;

  defaultOption.name = "Koch curve";
  defaultOption.init = "F";
  defaultOption.constants.clear();
  defaultOption.rules.push_back("F => F+F-F-F+F");
  defaultOption.angle = 90;
  defaultOption.iteration = 4;

  return defaultOption;
}

LSystemOption readSystemOption(std::string filepath) {
  LSystemOption option;

  std::ifstream ifs(filepath.c_str());
  std::string yml = std::string(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());

  ryml::Tree tree = ryml::parse(c4::csubstr{ yml.c_str(), yml.length() });

  {
    c4::csubstr v = tree["name"].val();
    std::string a(v.str, v.len);
    option.name = a;
  }

  {
    c4::csubstr v = tree["init"].val();
    std::string a(v.str, v.len);
    option.init = a;
  }

  {
    ryml::NodeRef node = tree["rules"];
    for (auto it : node) {
      c4::csubstr v = it.val();
      std::string a(v.str, v.len);
      option.rules.push_back(a);
    }
  }

  {
    ryml::NodeRef node = tree["angle"];
    node >> option.angle;
  }

  {
    
    c4::csubstr v = tree["constants"].val();
    std::string a(v.str, v.len);
    for (auto e : a) {
      option.constants.push_back(e);
    }
  }

  {
    ryml::NodeRef node = tree["iteration"];
    node >> option.iteration;
  }


  return option;
}