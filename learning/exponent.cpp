#include <iostream>

int powerOfTwo(int exponent) {
    return 2 << (exponent - 1);
}

int main() {
    std::cout << "2 raised to 1 = " << powerOfTwo(1) << '\n';
    std::cout << "2 raised to 2 = " << powerOfTwo(2) << '\n';
    std::cout << "2 raised to 3 = " << powerOfTwo(3) << '\n';
    std::cout << "2 raised to 4 = " << powerOfTwo(4) << '\n';
    std::cout << "2 raised to 5 = " << powerOfTwo(5) << '\n';
    std::cout << "2 raised to 6 = " << powerOfTwo(6) << '\n';
}
