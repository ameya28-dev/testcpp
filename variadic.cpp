#include <array>
#include <cassert>
#include <cstdio>
#include <iostream>

void print() {
    std::cout << std::endl;
}

template <typename T, typename... Args>
void print(T first, Args... args) {
    std::cout << first << " ";
    print(std::forward<Args>(args)...);
}

template <typename... Arguments>
class vtclass {};

vtclass<> vtinstance1;
vtclass<int> vtinstance2;
vtclass<float, bool> vtinstance3;

template <class B, class... A>
struct container {};

template <typename... Args>
void func(Args... args) {}

template <class... A, class... B>
void func_trailing(A... a, int s1, int s2, B... b) {
    // print("a:", std::forward<A>(a)...);
    // print("b:", std::forward<B>(b)...);

    if (sizeof...(a) == 0) {
        std::cout << "a packs 0 parameters\n";
    } else if (sizeof...(a) < s1) {
        std::cout << "a packs less parameters than s1(" << s1 << ")\n";
    } else if (sizeof...(a) == s1) {
        std::cout << "a packs same number of parameters as s1(" << s1 << ")\n";
    } else {
        std::cout << "a packs more parameters than s1(" << s1 << ")\n";
    }

    if (sizeof...(b) == 0) {
        std::cout << "b packs 0 parameters\n";
    } else if (sizeof...(b) < s2) {
        std::cout << "b packs less parameters than s2(" << s2 << ")\n";
    } else if (sizeof...(b) == s2) {
        std::cout << "b packs same number of parameters as s2(" << s2 << ")\n";
    } else {
        std::cout << "b packs more parameters than s2(" << s2 << ")\n";
    }
}

struct complex {
    float x, y;
};

/// Expression List
template <class... A>
void func1(A... arg) {
    assert(false);
}

void func1(int a1, int a2, int a3, int a4, int a5, int a6) {
    printf("call with(%d,%d,%d,%d,%d,%d)\n", a1, a2, a3, a4, a5, a6);
}

template <class... A>
int func2(A... args) {
    int size = sizeof...(A);
    switch (size) {
        case 0:
            func1(99, 99, 99, 99, 99, 99);
            break;
        case 1:
            func1(99, 99, args..., 99, 99, 99);
            break;
        case 2:
            func1(99, 99, args..., 99, 99);
            break;
        case 3:
            func1(args..., 99, 99, 99);
            break;
        case 4:
            func1(99, args..., 99);
            break;
        case 5:
            func1(99, args...);
            break;
        case 6:
            func1(args...);
            break;
        default:
            func1(0, 0, 0, 0, 0, 0);
    }
    return size;
}
///

template <typename... A>
void initializer_list(A... args) {
    std::array<int, sizeof...(args) + 5> array{99, 98, args..., 97, 96, 95};
    std::cout << "Initializer output: ";
    for (auto& i : array) {
        std::cout << i << " ";
    }
    std::cout << '\n';
}

int main() {
    print("Hello", "World", 1234);
    func();
    func(10);
    func(1, 2, 3, 45);
    func("Hey");

    func_trailing(1, 2, 3, 5, 6);  /// A => empty, B => {3,5,6}
    func_trailing<int, std::string, int>(1, {1, 2}, 2, 4, 5, 6);

    func2(1, 2, 3, 4, 5);

    initializer_list();
}
