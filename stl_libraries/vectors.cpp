#include <string>
#include <vector>
#include <array>
#include <iostream>
#include <unordered_map>

class Person
{
private:
    std::string name;
    int age;

public:
    Person();
    Person(std::string name, int age);
    void display();
};

void Person::display()
{
    std::cout << "Name:\t" << this->name << ", Age:\t" << this->age << std::endl;
}

Person::Person()
{
}

Person::Person(std::string name, int age)
{
    this->name = name;
    this->age = age;
}

const std::string& more_frequent(const std::unordered_map<std::string, int>& word_counts, const std::string& word1, const std::string& word2){
    return word_counts.at(word1) > word_counts.at(word2) ? word1 : word2;
}


template<std::size_t size>
void better_array(std::array<Person, size> arr){
    
}

template<typename T>
void print(T value){
    std::cout << value;
}

int main()
{
    std::array<Person, 5> a;
    std::vector<Person> v;
    v.push_back(Person("Ameya", 24));
    v.emplace_back("Shreeya", 18);
    for (auto p : v)
    {
        p.display();
    }
    
    

    a[0] = Person("Ameya", 45);

    std::unordered_map<std::string, std::string> colors = {
            {"RED",   "#FF0000"},
            {"GREEN", "#00FF00"},
            {"BLUE",  "#0000FF"}
    };

    for(const auto [name, hex]:colors){
        std::cout << "Name:\t" << name << "\tColor:\t" << hex; 
    }

    if (     __cplusplus == 202101L) std::cout << "C++23";
    else if (__cplusplus == 202002L) std::cout << "C++20";
    else if (__cplusplus == 201703L) std::cout << "C++17";
    else if (__cplusplus == 201402L) std::cout << "C++14";
    else if (__cplusplus == 201103L) std::cout << "C++11";
    else if (__cplusplus == 199711L) std::cout << "C++98";
    else std::cout << "__cplusplus: " << __cplusplus;
    std::cout << std::endl;

    return 0;
}