#include <iostream>

void foo() {}

struct Entity {
    int x, y;

    void print() {
        std::cout << x << ", " << y << '\n';
    }
};

/// Imagine a static method is converted to this:
//  void print() {
//     std::cout << x << ", " << y << '\n';
// }

/// And non static method is converted to this:
// void print(Entity* e) {
//     std::cout << e->x << ", " << e->y << '\n';
// }

/// Now it is probably clear why a static method cannot access non static members

int main() {
    Entity e1;
    e1.x = 2;
    e1.y = 3;

    Entity e2;
    e2.x = 5;
    e2.y = 8;

    e1.print();
    e2.print();
}