#include <iostream>
#include <string>

class Printable {
   public:
    virtual std::string GetClassName() = 0;
};

class Entity : public Printable {
   public:
    virtual std::string GetName() { return "Entity"; }

    std::string GetClassName() override { return "Entity"; }
};

class Player : public Entity {
   private:
    std::string m_Name;

   public:
    Player(const std::string& name) : m_Name(name) {}

    std::string GetName() override { return m_Name; }

    std::string GetClassName() override { return "Player"; }
};

void PrintName(Entity* entity) {
    std::cout << entity->GetName() << std::endl;
}

void Print(Printable* obj) {
    std::cout << obj->GetClassName() << std::endl;
}

class Base {
   public:
    Base() { std::cout << "Base Constructed\n"; }
    virtual ~Base() { std::cout << "Base Destructed\n"; }
};

class Derived : public Base {
   public:
    Derived() {
        m_Array = new int[5];
        std::cout << "Derived Constructed\n";
    }

    ~Derived() {
        delete[] m_Array;
        std::cout << "Derived Destructed\n";
    }

   private:
    int* m_Array;
};

int main() {
    Entity* e = new Entity();
    Print(e);

    Player* p = new Player("Ameya");
    Print(p);

    std::cout << "------------------------------\n";
    Base* base = new Base();
    delete base;

    std::cout << "------------------------------\n";

    Derived* derived = new Derived();
    delete derived;

    std::cout << "------------------------------\n";

    Base* poly = new Derived();
    delete poly;
}