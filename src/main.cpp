#include <stdafx.hpp>
#include <imgui/imgui.h>
#include <LSystem.hpp>

using namespace std;

int main(int argc, char const *argv[]) {

    LSystemBase l("t");
    l.add_rule("t => tt+t");
    l.show_rules();
    return 0;
}
