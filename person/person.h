#include <string>

class Person {
   private:
    std::string name;
    int age;

   public:
    Person();
    Person(std::string name, int age);
    void print();
};
