#include <stdafx.hpp>
#include <imgui/imgui.h>
#include <LSystem.hpp>

using namespace std;

int main(int argc, char const *argv[]) {

    LSystemBase l("aaa");
    l.add_rule("s => asa");
    l.add_rule("a => aa+s");
    l.show_rules();

    l.iterate();
    cout << l.get_condition() << endl;
    return 0;
}
