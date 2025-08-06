#include <string>

class Person {
   private:
    std::string inner_thought;

   protected:
    double insurance_number;

   public:
    std::string name;
};

class Wife : public Person {
    void print() {
        insurance_number;
        name;
    }
};

class Child : protected Person {
    void print() {
        name;
        insurance_number;
    }
};

class Collegue : private Person {
    void print() {
        name;
        insurance_number;
    }
};

int main() {
    Person person;
    Wife wife;
    Child child;
}