#include <iostream>
#include <string>

#include "vector.h"

template <typename T>
void print_vector(const Vector<T>& vector) {
    for (int i = 0; i < vector.size(); i++) std::cout << vector[i] << '\n';
}

class Point3 {
    float x = 0.0f, y = 0.0f, z = 0.0f;

    Point3() {}
    Point3(float scalar) : x(scalar), y(scalar), z(scalar) {}
    Point3(float x, float y, float z) : x(x), y(y), z(z) {}

    Point3(const Point3& other) : x(other.x), y(other.y), z(other.z) { std::cout << "Copied\n"; }
    Point3(const Point3&& other) : x(other.x), y(other.y), z(other.z) { std::cout << "Moved\n"; }
    ~Point3() { std::cout << "Destroyed\n"; }
};

int main() {
    Vector<std::string> v;
    v.push_back("Hello");
    v.push_back("world");
    v.push_back("Hi");
    v.push_back("Welcome");
    print_vector(v);
}