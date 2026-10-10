#include <iostream>
#include <type_traits>

template <typename T>
T&& forward(std::remove_reference_t<T>& t) {
    return static_cast<T&&>(t);
}

template <typename T>
T&& forward(std::remove_reference_t<T>&& t) {
    return static_cast<T&&>(t);
}

void print(int&) {
    std::cout << "lvalue\n";
}

void print(int&&) {
    std::cout << "rvalue\n";
}

template <typename T>
void doWork(T&& t) {
    print(forward<T>(t));
}

int main() {
    int num{};
    doWork(num);
    doWork(42);
    doWork(std::move(num));
}
