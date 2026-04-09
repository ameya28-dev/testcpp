#include <iostream>
#include <tuple>

int main() {
    auto t = std::tuple<int, const int, double, double>(1, 2, 5.6, 8.9);
    const int &a = std::get<int>(t);
    const auto b = std::get<1>(t);
    const auto c = std::get<2>(t);

    std::get<int>(t) = 12;

    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
}
