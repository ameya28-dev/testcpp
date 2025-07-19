#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>
#include <variant>

struct Circle {
    double radius;
};
struct Rectangle {
    double width, height;
};
struct Square {
    double side;
};

struct Triangle {
    double base, height;
};

using Shape = std::variant<Circle, Rectangle, Square, Triangle>;

template <class... Ts>
struct overloaded : Ts... {
    using Ts::operator()...;
};
template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

double area(const Shape& shape) {
    return std::visit(
        overloaded{
            [](const Circle& c) { return M_PI * c.radius * c.radius; },
            [](const Rectangle& r) { return r.width * r.height; },
            [](const Square& s) { return s.side * s.side; },
            [](const Triangle& t) { return 0.5 * t.base * t.height; }},
        shape);
}

int main() {
    Shape s1 = Circle{10};
    Shape s2 = Rectangle{10, 15};
    Shape s3 = Square{10};

    std::cout << "Area of circle: " << area(s1) << '\n';
    std::cout << "Area of rectangle: " << area(s2) << '\n';
    std::cout << "Area of square: " << area(s3) << '\n';
}