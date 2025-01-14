#include "person.h"
#include <iostream>

Person::Person() : name(""), age(0) {}

Person::Person(std::string name, int age) : name(name), age(age) {}

void Person::print() {
    std::cout << "Name: " << this->name << ", Age: " << this->age << std::endl;
}