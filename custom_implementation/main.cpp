#include <iostream>

#include "array.h"
#include "vector.h"

template <size_t S>
std::ostream& operator<<(std::ostream& stream, const Array<int, S>& arr) {
    for (int i = 0; i < S; i++) {
        stream << arr[i] << '\t';
    }
    stream << std::endl;
    return stream;
}

template <typename T>
void PrintVector(const Vector<T>& vec) {
    for (size_t i = 0; i < vec.GetSize(); i++) {
        std::cout << vec[i] << '\t';
    }
    std::cout << "\n--------------------------\n";
}

struct Coordinate {
    float x, y, z;
    int* memory_block = nullptr;
    Coordinate() : x(0.0f), y(0.0f), z(0.0f) {
        memory_block = new int[5];
    }
    Coordinate(float scalar) : x(scalar), y(scalar), z(scalar) { memory_block = new int[5]; }
    Coordinate(float x, float y, float z) : x(x), y(y), z(z) { memory_block = new int[5]; }

    Coordinate(const Coordinate& other) = delete;  //: x(other.x), y(other.y), z(other.z) { std::cout << "Copy" << std::endl; }
    Coordinate(Coordinate&& other) : x(other.x), y(other.y), z(other.z) {
        memory_block = other.memory_block;
        other.memory_block = nullptr;
        std::cout << "Move" << std::endl;
    }
    ~Coordinate() {
        delete[] memory_block;
        std::cout << "Destroyed" << std::endl;
    }

    Coordinate& operator=(const Coordinate& other) = delete;
    // {
    //     std::cout << "Copied" << std::endl;
    //     x = other.x;
    //     y = other.y;
    //     z = other.z;
    //     return *this;
    // }

    Coordinate& operator=(Coordinate&& other) {
        std::cout << "Moved" << std::endl;
        x = other.x;
        y = other.y;
        z = other.z;
        memory_block = other.memory_block;
        other.memory_block = nullptr;
        return *this;
    }
};

void PrintVector(const Vector<Coordinate>& vec) {
    for (size_t i = 0; i < vec.GetSize(); i++) {
        std::cout << vec[i].x << ", " << vec[i].y << ", " << vec[i].z << '\n';
    }
    std::cout << "\n--------------------------\n";
}

int main() {
    Array<int, 5> arr;
    arr[4] = 7;
    std::cout << arr.getSize() << std::endl;
    std::cout << arr;

    Vector<std::string> vec;
    vec.EmplaceBack("Ameya");
    vec.EmplaceBack("is");
    vec.EmplaceBack("good.");
    // PrintVector(vec);

    std::cout << "Index based loops\n";
    for(size_t i = 0; i < vec.GetSize() ; i++){
        std::cout << vec[i] << '\t';
    }
    std::cout << '\n';
 
    std::cout << "Range based loops\n";
    for(std::string s : vec){
        std::cout << s << '\t';
    }
    std::cout << '\n';
    
    std::cout << "Iterator based loops\n";
    for(Vector<std::string>::Iterator it = vec.begin() ; it != vec.end(); it++){
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

    return 0;
}