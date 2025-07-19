#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

std::ostream& operator<<(std::ostream& instream, const std::vector<int> v) {
    instream << "std::vector<int>{";
    for (auto it = v.begin(); it != v.end(); it++) {
        instream << *it;
        if (it != v.end() - 1) {
            instream << ", ";
        }
    }

    instream << "}";

    return instream;
}

std::ostream& operator<<(std::ostream& out, const std::set<int>& set) {
    if (set.empty()) {
        return out << "{}";
    }
    out << "std::set<int>{ " << *set.begin();
    std::for_each(std::next(set.begin()), set.end(), [&out](const int& element) {
        out << ", " << element;
    });
    return out << " }";
}

int main() {
    {
        std::cout << "Erase-remove idiom:\n";

        std::vector<int> v1{1, 2, 4, 6, 7, 2, 3, 5, 7, 2, 9};

        auto it = std::remove(v1.begin(), v1.end(), 2);
        v1.erase(it, v1.end());

        std::cout << v1 << std::endl;
    }

    {
        std::cout << "\nTransform:\n";
        std::vector<int> v{1, 2, 4, 6, 7, 2, 3, 5, 7, 2, 9};

        std::vector<int> res;

        std::transform(v.cbegin(), v.cend(), std::back_inserter(res), [](int a) { return a * a; });
        std::cout << res << std::endl;
    }

    {
        std::cout << "\nFilter out even numbers from vector and square the remaining numbers:\n";
        std::vector<int> v{1, 2, 4, 6, 7, 2, 3, 5, 7, 2, 9};
        std::cout << "Original numbers:\t" << v << std::endl;
        v.erase(std::remove_if(v.begin(), v.end(), [](int a) { return a % 2 == 0; }), v.end());
        std::for_each(v.begin(), v.end(), [](int& a) { a *= a; });
        std::cout << "Filter even numbers and square remaining:\t" << v << std::endl;
        std::set<int> s(v.begin(), v.end());
        std::cout << "Only unique elements:\t" << s << std::endl;
    }

    {
        std::set<int> s{2, 5, 1, 0};
        std::cout << s << std::endl;
    }
}