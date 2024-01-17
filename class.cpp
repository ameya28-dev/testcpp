#include <iostream>
#include <array>

class Person{
public:
    std::string name;

    Person(std::string name)
    {
        // std::cout << name << '\n';
        // std::cout << this->name << '\n';
        this->name = name;
    }

    void assignNewName(std::string name)
    {
        this->name = name;
    }

    double areaOfCircle(double radius)
    {
        return this->pi * radius * radius;
    }

private:
    const double pi = 3.14;
};

void assignNewName(Person person)
{
    person.name = "Ameya";
    std::cout << "Inside function: \t" << person.name << '\n';
}

void assignNewName(Person *person)
{
    person->name = "Ashwin";
}

int main()
{
    Person person = Person("Shreeya");
    Person *p = &person;
    p->name = "Vighnesh";
    std::cout << "Inside main: \t" << person.name << '\n';
    assignNewName(person);
    std::cout << "Inside main: \t" << person.name << '\n';
    person.assignNewName("Ameya");
    std::cout << "Inside main: \t" << person.name << '\n';
    assignNewName(&person);
    std::cout << "Inside main: \t" << person.name << '\n';
    std::cout << person.areaOfCircle(2) << '\n';

    int arr[] = {1, 3, 5, 6, 7, 8, 10, 11, 12, 13};
    std::cout << int(sizeof(arr));

    const int n = 10;
    std::array<int, n> array{};

    return 0;
}