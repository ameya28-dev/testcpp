#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>

class Complex {
   private:
    double a, b;

   public:
    Complex(const double x, const double y) : a(x), b(y) {}
    ~Complex() = default;

    Complex(const Complex& c) = delete;
    Complex& operator=(const Complex& c) = delete;

    Complex(const Complex&& c) noexcept : a(c.a), b(c.b) {}
    Complex& operator=(Complex&& c) noexcept {
        a = c.a;
        b = c.b;
        return *this;
    }

    constexpr double modulus() const {
        return sqrt(pow(a, 2) + pow(b, 2));
    }

    constexpr double arg() const {
        // the argument value of the number
        double angle = atan(b / a);
        angle = angle * 180 / M_PI;
        return angle;
    }

    void print_number() const {
        if (b < 0) {
            std::cout << a << "-" << -b << 'i' << '\n';
        } else
            std::cout << a << "+" << b << 'i' << '\n';
    }

    Complex operator+(const Complex& c1) const {
        return {a + c1.a, b + c1.b};
    }

    Complex operator*(const Complex& c1) const {
        return {a * c1.a - b * c1.b, a * c1.b + b * c1.a};
    }

    Complex operator/(const Complex& c1) const {
        if (c1.a == 0 && c1.b == 0) {
            std::cout << "Division by zero error";
            return {0, 0};
        }
        return (*this * c1) / c1.modulus();
    }

    Complex operator/(const double modulus) const {
        return {a / modulus, b / modulus};
    }
};

int main() {
    Complex c1(3, 4), c2(12, 7);
    Complex c3 = c1 + c2;
    c3.print_number();
    Complex ctest(1, 0);
    Complex c4 = c1 * ctest;
    c4.print_number();
    Complex c5 = ctest / c1;
    c5.print_number();
    std::cout << c1.arg() << '\n';
    Complex c6 = (c1 + c2) + c3;
    c6.print_number();

    auto x = c6.modulus();
    x = 10;
    return 0;
}