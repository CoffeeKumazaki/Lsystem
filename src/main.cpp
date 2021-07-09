#include <stdafx.hpp>
#include "imgui/imgui.h"
#include <LSystem.hpp>
#include <LTurtle.hpp>

using namespace std;

double deg2rad (double degrees) {
    return degrees * 4.0 * atan (1.0) / 180.0;
}

int main(int argc, char const *argv[]) {

    LSystemOption option = getDefaultSystemOption();
    if (argc>0) {
        option = readSystemOption(argv[1]);
    } 

    LSystemBase l(option.init, option.rules);

    l.show_rules();

    l.iterate(option.iteration);
    auto res = l.get_condition();
    cout << "[result]" << endl;
    cout << "  " << res << endl;

    LTurtle t;
    t.init(option.step, deg2rad(option.angle));
   // t.moveto({100, 700});
    t.interpret(res);
    t.draw();

    return 0;
}
