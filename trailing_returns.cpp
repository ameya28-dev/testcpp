#include <iostream>
#include <variant>

auto s = [](bool f) {
    if (f) return 1;
    return 0;
};

using BoolReturnsInt = int (*)(bool);

auto func(bool x, BoolReturnsInt fun) { return fun(x); }

int main() {
    std::cout << func(true, s) << '\n';
    std::cout << func(false, s) << '\n';
}