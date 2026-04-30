#include "vector.h"
#include <algorithm>
#include <iostream>
#include <type_traits>
#include <vector>

struct Coordinate {
    float x, y, z;
    int* memoryBlock = nullptr;

    Coordinate() : x(0.0f), y(0.0f), z(0.0f) {
        memoryBlock = new int[5];
    }

    Coordinate(float scalar) : x(scalar), y(scalar), z(scalar) {
        memoryBlock = new int[5];
    }

    Coordinate(float x, float y, float z) : x(x), y(y), z(z) {
        memoryBlock = new int[5];
    }

    Coordinate(const Coordinate& other) = delete;

    //: x(other.x), y(other.y), z(other.z) { std::cout << "Copy" << std::endl; }

    Coordinate(Coordinate&& other) : x(other.x), y(other.y), z(other.z) {
        memoryBlock       = other.memoryBlock;
        other.memoryBlock = nullptr;
        std::cout << "Move" << std::endl;
    }

    ~Coordinate() {
        delete[] memoryBlock;
        std::cout << "Destroyed" << std::endl;
    }

    Coordinate& operator=(const Coordinate& other) = delete;

    Coordinate& operator=(Coordinate&& other) {
        std::cout << "Moved" << std::endl;
        x                 = other.x;
        y                 = other.y;
        z                 = other.z;
        memoryBlock       = other.memoryBlock;
        other.memoryBlock = nullptr;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, const Coordinate& coord) {
        return out << '{' << coord.x << ", " << coord.y << ", " << coord.z << "}";
    }
};

template <typename T, typename = void>
struct IsStreamable : std::false_type {};

template <typename T>
struct IsStreamable<T, std::void_t<decltype(std::cout << std::declval<T>())>> : std::true_type {};

template <typename T>
auto PrintVector(const Vector<T>& vec) -> std::enable_if_t<IsStreamable<T>::value, void> {
    std::cout << "[";
    if (!vec.IsEmpty()) {
        std::cout << *vec.begin();
        std::for_each(std::next(vec.begin()), vec.end(), [&](const T& t) { std::cout << ", " << t; });
    }
    std::cout << "]\n--------------------------\n";
}

int main() {
    Vector<std::string> vec;
    vec.EmplaceBack("Ameya");
    vec.EmplaceBack("is");
    vec.EmplaceBack("good.");
    // PrintVector(vec);

    std::cout << "Index based loops\n";
    for (size_t i = 0; i < vec.GetSize(); i++) {
        std::cout << vec[i] << '\t';
    }
    std::cout << '\n';

    std::cout << "Range based loops\n";
    for (std::string s : vec) {
        std::cout << s << '\t';
    }
    std::cout << '\n';

    std::cout << "Iterator based loops\n";
    for (Vector<std::string>::Iterator it = vec.begin(); it != vec.end(); it++) {
        std::cout << *it << '\t';
    }
    std::cout << '\n';


    {
        Vector<Coordinate> v;
        v.EmplaceBack();
        v.EmplaceBack(10.0);
        v.EmplaceBack(1, 2, 3);
        v.EmplaceBack(5);
        v.EmplaceBack();
        v.PopBack();
        v.PopBack();
        PrintVector(v);
        v.EmplaceBack(5);
        v.EmplaceBack(6, 8, 3);
        PrintVector(v);
        v.Clear();
        v.EmplaceBack(6, 8, 3);
        PrintVector(v);
    }

    std::vector<int> v{1, 2, 3, 4, 5};

    return 0;
}
