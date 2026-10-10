#include <cmath>
#include <iostream>

double epsilon = 0.0001;

double function(int x) {
    return x * x * x - 3 * x * x - 5 * x - 1;
}

double derivative(int x) {
    return 3 * x * x - 6 * x - 5;
}

int main() {
    double initial = 4;

    auto h = function(initial) / derivative(initial);

    while (std::abs(h) >= epsilon) {
        h = function(initial) / derivative(initial);

        initial -= h;
    }

    std::cout << "Final solution = " << initial << std::endl;
}