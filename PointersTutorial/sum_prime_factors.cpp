#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <set>
#include <vector>

bool is_prime(std::set<int>& primes, const int n) {
    if (primes.find(n) != primes.cend()) {
        return true;
    }
    int p = 2;
    while (p * p <= n) {
        if (n % p == 0) return false;
        p++;
    }

    primes.insert(n);
    return true;
}

std::ostream& operator<<(std::ostream& instream, const std::set<int>& s) {
    for (const int i : s) {
        instream << i << '\t';
    }
    return instream;
}

bool is_prime(std::vector<int>& primes, const int n) {
    if (std::find(primes.cbegin(), primes.cend(), n) != primes.cend()) {
        return true;
    }
    int p = 2;
    while (p * p <= n) {
        if (n % p == 0) return false;
        p++;
    }

    primes.emplace_back(n);
    return true;
}

std::ostream& operator<<(std::ostream& instream, const std::vector<int>& s) {
    for (const int i : s) {
        instream << i << '\t';
    }
    return instream;
}

int main() {
    std::set<int> primes;

    const std::vector<int> input{5, 10, 12, 24, 45, 97, 91, 56, 1001, 11};

    for (const int n : input) {
        for (int i = 2; i <= n; i++) {
            if (n % i) continue;
            if (!is_prime(primes, i)) continue;
        }
        std::cout << n << "\tprimes:\t" << primes << '\n';
    }

    {
        std::cout << "Using vectors\n";

        std::vector<int> primes;
        for (const int n : input) {
            for (int i = 2; i <= n; i++) {
                if (n % i) continue;
                if (!is_prime(primes, i)) continue;
            }
            std::cout << n << "\tprimes:\t" << primes << '\n';
        }
        std::cout << std::accumulate(primes.begin(), primes.end(), decltype(primes)::value_type(0)) << '\n';
        std::cout << std::reduce(primes.begin(), primes.end()) << '\n';
    }

    {
        std::function<int(int)> square = [](int x) { return x*x; };
        std::cout << square(10) << std::endl;
    }

    int sum = 0;
    for (const int s : primes) sum += s;
    std::cout << sum << "\n";
}