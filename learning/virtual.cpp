#include <iostream>

class Animal {
public:
    virtual void speak() {
        std::cout << "...\n";
    }
};

class Dog : public Animal {
public:
    void speak() override {
        std::cout << "Woof\n";
    }
};

struct Simple {
    int a, b;

    void foo() {}
};

struct Polymorphic {
    int a, b;

    virtual void foo() {}
};

int main() {
    Animal a;
    a.speak(); // ...
    Dog d;
    d.speak(); // woof
    Animal d2 = Dog();
    d2.speak(); // ... (if speak in Animal is not virtual)

    Animal* a1 = &a;
    Animal* a2 = &d;
    a1->speak(); // ...
    a2->speak(); // ... (if speak in Animal is not virtual)

    std::cout << "------------------------------------\n";

    std::cout << "Size of Simple: " << sizeof(Simple) << '\n';
    std::cout << "Size of Polymorphic: " << sizeof(Polymorphic) << '\n';
}
