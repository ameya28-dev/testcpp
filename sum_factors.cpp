#include <cmath>
#include <iostream>
using namespace std;

// Function to compute the sum of all factors of n
long long sumOfFactors(int n) {
    long long sum = 0;
    int sqrt_n = sqrt(n);
    for (int i = 1; i <= sqrt_n; ++i) {
        div_t d = std::div(n, i);

        if (d.rem == 0) {
            sum += i;
            if (d.quot != i) sum += d.quot;
        }
    }
    return sum;
}

long long sumOfFactorsV2(int n) {
    long long res = 1;
    int original_n = n;
    for (int i = 2; i * i <= n; ++i) {
        long long curr_sum = 1, curr_term = 1;
        while (n % i == 0) {
            n /= i;
            curr_term *= i;
            curr_sum += curr_term;
        }
        res *= curr_sum;
    }
    // If n is a prime greater than 2
    if (n > 1) res *= (1 + n);
    return res;
}

int main() {
    auto sum = sumOfFactors(27720);
    std::cout << sum << '\n';
    return 0;
}
