#include <iostream>
struct S {
    int x;

    explicit S(int x) : x(x) { std::cout << "construct S(" << x << ")\n"; }
    S(const S& other) : x(other.x) { std::cout << "copy S(" << x << ")\n"; }
};

S make_value(int x) {
    return S(x);
}

S make_double(int x) {
    S s = make_value(x);
    s.x = 2 * x;
    return s;
}

S no_ellision(int x) {
    S s1(x);
    S s2(x);

    if (x > 0)
        return s1;
    else
        return s2;
}

void in_values(S s) {
    std::cout << "answer: " << s.x << "\n";
}

int main() {
    S s = make_double(21);
    return 0;
}