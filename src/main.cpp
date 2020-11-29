#include <stdafx.hpp>
#include "imgui/imgui.h"
#include <LSystem.hpp>
#include <LTurtle.hpp>

using namespace std;

int main(int argc, char const *argv[]) {

    LSystemBase l("F");
    l.add_rule("F => F+F−F−F+F");
    l.show_rules();

    l.iterate(3);
    auto res = l.get_condition();
    cout << "[result]" << endl;
    cout << "  " << res << endl;

    LTurtle t;
    t.init(100, 90);
    t.interpret(res);
    t.draw();

    return 0;
}
