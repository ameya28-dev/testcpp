#include "array.h"
#include <algorithm>
#include <array>
#include <iostream>

template <typename T, size_t S>
std::ostream& operator<<(std::ostream& out, const Array<T, S>& arr) {
    out << '[';
    if (!arr.isEmpty()) {
        out << *arr.begin();
        std::for_each(std::next(arr.begin()), arr.end(), [&](const T t) { out << ", " << t; });
    }
    return out << ']';
}

template <typename T, size_t S>
std::ostream& operator<<(std::ostream& out, const std::array<T, S>& arr) {
    out << '[';
    if (!arr.empty()) {
        out << *arr.begin();
        std::for_each(std::next(arr.begin()), arr.end(), [&](const T t) { out << ", " << t; });
    }
    return out << ']';
}

void stdArrayInitialization() {
    std::array<int, 5> a1{1, 2};
    std::cout << "a1: " << a1 << '\n';
    std::array<int, 5> a2{};
    std::cout << "a2: " << a2 << '\n';
    std::array<int, 5> a3;
    std::cout << "a3: " << a3 << '\n';
    std::array<int, 5> a4{1, 2, 3, 4, 5};
    std::cout << "a4: " << a4 << '\n';
    std::array a5{1, 2, 3, 4, 5, 6};
    std::cout << "a5: " << a5 << '\n';

    auto it   = a5.begin();
    auto pre  = ++it;
    auto post = it++;

    std::cout << "it = " << *it << ", pre = " << *pre << ", post = " << *post << '\n';
}

void customArrayInitialization() {
    Array<int, 5> a1{1, 2};
    std::cout << "custom a1: " << a1 << '\n';
    Array<int, 5> a2{};
    std::cout << "custom a2: " << a2 << '\n';
    Array<int, 5> a3;
    std::cout << "custom a3: " << a3 << '\n';
    Array<int, 5> a4{1, 2, 3, 4, 5};
    std::cout << "custom a4: " << a4 << '\n';
    Array a5{1, 2, 3, 4, 5, 6};
    std::cout << "custom a5: " << a5 << '\n';

    try {
        Array<int, 5> arr{1, 2, 3, 4, 5, 6};
        std::cout << "custom arr: " << arr << '\n';
    } catch (const std::out_of_range& ex) {
        std::cerr << ex.what() << '\n';
    }
}

int main() {
    Array<int, 5> arr;
    arr[4] = 7;
    std::cout << arr.getSize() << std::endl;
    std::cout << arr << '\n';

    stdArrayInitialization();
    customArrayInitialization();

    auto it = std::next(arr.begin());
}
