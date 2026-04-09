#include <climits>
#include <cmath>
#include <concepts>
#include <cstring>
#include <iostream>
#include <limits>
#include <type_traits>

template <typename T>
concept Addable = requires(T a, T b) {
    { a + b } -> std::convertible_to<T>;
};

auto add(Addable auto a, Addable auto b) -> Addable auto { return (a + b); }

template <Addable T, Addable... Args>
auto add(T first, Args... args) -> T {
    return first + add(std::forward<Args>(args)...);
}

struct Complex {
    double x, y;

    Complex(const double x, const double y) : x(x), y(y) {}

    Complex operator+(const Complex& other) {
        return Complex(x + other.x, y + other.y);
    }

    Complex operator+(Complex&& other) {
        return Complex(x + other.x, y + other.y);
    }

    friend std::ostream& operator<<(std::ostream& stream, const Complex& c) {
        if (c.x == 0) {
            return stream << c.y << 'i';
        }

        if (c.y == 0) {
            return stream << c.x;
        }

        char delimiter = (c.y < 0) ? '-' : '+';

        return stream << c.x << delimiter << std::abs(c.y) << "i";
    }
};

int main() {
    std::cout << INT_MAX << '\n';
    std::cout << std::numeric_limits<int>::max() << '\n';
    std::cout << add(1, 2) << '\n';
    std::cout << add(1, 2, 3) << '\n';
    std::cout << add(1.4, 6.7) << '\n';
    std::cout << add(std::string{"Hello "}, std::string{"World!"}) << '\n';
    std::cout << add(Complex(1, 2), Complex(-1, -2.556)) << '\n';
}