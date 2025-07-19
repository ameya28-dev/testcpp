#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

static size_t size = 0;

void* operator new(size_t s) {
    size += s;

    void* p = malloc(s);
    return p;
}

template <std::size_t S, std::size_t T>
void foo(const std::array<int, S>& a1, const std::array<int, T>& a2) {
    for (auto i : a1) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;

    for (auto i : a2) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}

std::ostream& operator<<(std::ostream& out, const std::vector<int>& vec) {
    if (vec.empty()) {
        return out << "{}";
    }
    out << "std::vector<int>{ " << *vec.begin();
    std::for_each(std::next(vec.begin()), vec.end(), [&out](const int& element) {
        out << ", " << element;
    });
    return out << " }";
}

std::vector<int> split(const std::vector<int>& vec, int split_at) {
    std::vector<int> res(vec.size());
    std::vector<int> left{vec.begin(), vec.begin() + split_at};
    std::vector<int> right{vec.begin() + split_at, vec.end()};
    auto it = std::copy(right.begin(), right.end(), res.begin());
    std::copy(left.begin(), left.end(), it);
    return res;
}

void split_2(std::vector<int>& vec, int split_at) {
    std::rotate(vec.begin(), vec.begin() + split_at, vec.end());
}

int main() {
    std::array<int, 5> a1{1, 2, 4, 6, 6};
    std::array<int, 6> a2{1, 2, 4, 6, 6, 8};
    std::sort(a2.begin(), a2.end());

    foo(a1, a2);

    std::vector<int> v{1, 2, 3, 4, 5};
    // std::cout << split(v, 2) << std::endl;
    split_2(v, 2);
    std::cout << v << std::endl;
    std::cout << "Allocated " << size << " bytes\n";
}