#include <iostream>
#include <optional>

std::optional<int> divide(double a, double b) {
    if (b == 0) return {};
    return a / b;
}

int main() {
    int a = 10, b = 0;
    auto result = divide(a, b);
    if (result) {
        std::cout << a << '/' << b << '=' << *result << '\n';
    } else {
        std::cout << "trying to divide by 0\n";
    }
}