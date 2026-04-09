#include <chrono>
#include <iostream>
#include <vector>

struct Timer {
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    std::chrono::duration<double> duration;

    Timer();
    ~Timer();
};

Timer::Timer() {
    start = std::chrono::high_resolution_clock::now();
}

Timer::~Timer() {
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;

    std::cout << "Timer took " << duration.count() * 1000.0 << "ms" << std::endl;
}

std::vector<int> primes(const size_t n) {
    Timer t;
    std::vector<int> res{};

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
        if (sieve[i]) res.emplace_back(i);
    }

    return res;
}

void print(const std::vector<int>& vec) {
    Timer t;
    for (int v : vec) {
        std::cout << v << "\t";
    }
}

float pi(int n) {
    Timer t;
    float sum = 0;
    int sign = 1;
    // printf("sum: %f\t", sum);
    // printf("sign: %d\n", sign);

    for (int i = 1; i < 2 * n; i = i + 2) {
        sum = sum + (4.0 / i) * sign;
        sign = sign * -1;
        // printf("sum: %f\t", sum);
        // printf("sign: %d\n", sign);
    }
    return sum;
}

int main() {
    // std::vector<int> res = primes(1000000);
    // print(res);

    std::cout << pi(100000);

    return 0;
}