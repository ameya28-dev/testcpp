#include <iostream>

void print() {
    std::cout << std::endl;
}

template <typename T, typename... Args>
void print(T first, Args... args) {
    std::cout << first << " ";
    print(std::forward<Args>(args)...);
}

int main() {
    print("Hello", "World", 1234);
}
