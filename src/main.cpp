#include <stdafx.hpp>
#include "imgui/imgui.h"
#include <LSystem.hpp>
#include <LTurtle.hpp>

using namespace std;

double deg2rad (double degrees) {
    return degrees * 4.0 * atan (1.0) / 180.0;
}

int main(int argc, char const *argv[]) {

    LSystemBase l("F");
    l.add_rule("F => F+F-F-F+F");
    l.show_rules();

    l.iterate(4);
    auto res = l.get_condition();
    cout << "[result]" << endl;
    cout << "  " << res << endl;

    LTurtle t;
    t.init(50, deg2rad(90));
   // t.moveto({100, 700});
    t.interpret(res);
    t.draw();

    return 0;
}
