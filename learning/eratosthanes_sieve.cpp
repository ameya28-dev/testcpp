#include <chrono>
#include <cstddef>
#include <iostream>
#include <vector>

struct Timer {
    Timer(const char* title);
    ~Timer();

    const char* title;
    const std::chrono::time_point<std::chrono::steady_clock> start;
};

Timer::Timer(const char* title) : title(title), start(std::chrono::steady_clock::now()) {}

Timer::~Timer() {
    auto end      = std::chrono::steady_clock::now();
    auto duration = end - start;

    std::cout << "(" << title << ") Timer took "
              << std::chrono::duration_cast<std::chrono::microseconds>(duration).count() << " microseconds" << '\n';
}

std::vector<int> primes(const size_t n) {
    Timer t{"Primes"};
    std::vector<int> res;
    res.reserve(n / 2);

    std::vector<bool> sieve(n + 1, true);

    size_t p = 2;

    while (p * p <= n) {
        if (sieve[p]) {
            for (int j = p * p; j <= n; j += p) {
                sieve[j] = false;
            }
        }

        p++;
    }

    for (size_t i = 2; i < n; i++) {
        if (sieve[i]) {
            res.emplace_back(i);
        }
    }

    return res;
}

void print(const std::vector<int>& vec) {
    Timer t{"print"};
    for (int v : vec) {
        std::cout << v << "\t";
    }
    std::cout << '\n';
}

float pi(int n) {
    Timer t{"pi"};
    float sum = 0;
    int sign  = 1;
    // printf("sum: %f\t", sum);
    // printf("sign: %d\n", sign);

    for (int i = 1; i < 2 * n; i = i + 2) {
        sum  = sum + (4.0 / i) * sign;
        sign = sign * -1;
        // printf("sum: %f\t", sum);
        // printf("sign: %d\n", sign);
    }
    return sum;
}

int main() {
    auto limit           = 1e7;
    std::vector<int> res = primes(limit);
    std::cout << "Number of primes below " << limit << " is: " << res.size() << '\n';
    // print(res);

    std::cout << pi(100000);

    return 0;
}
