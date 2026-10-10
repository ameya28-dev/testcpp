#include <any>
#include <iostream>
#include <string>
#include <variant>

union u {
    int x;
    char y;
};

using v = std::variant<int, char>;

int main() {
    std::cout << "size of char: " << sizeof(char) << '\n';
    std::cout << "size of int: " << sizeof(int) << '\n';
    std::cout << "size of string: " << sizeof(std::string) << '\n';
    std::cout << "size of u: " << sizeof(u) << '\n';
    std::cout << "size of v: " << sizeof(v) << '\n';
    std::cout << "size of std::any: " << sizeof(std::any) << '\n';
}
