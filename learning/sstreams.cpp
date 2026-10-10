#include <iostream>
#include <sstream>
#include <type_traits>

static constexpr auto bold       = "\033[1m";
static constexpr auto italic     = "\033[3m";
static constexpr auto reset      = "\033[0m";
static constexpr auto boldItalic = "\033[1;3m";

void sizeAndAlignments() {
    std::cout << "Size of std::ostringstream = " << sizeof(std::ostringstream) << '\n';
    std::cout << "Alignment of std::ostringstream = " << std::alignment_of_v<std::ostringstream> << "\n\n";
    std::cout << "Size of std::istringstream = " << sizeof(std::istringstream) << '\n';
    std::cout << "Alignment of std::istringstream = " << std::alignment_of_v<std::istringstream> << "\n\n";
    std::cout << "Size of std::stringstream = " << sizeof(std::stringstream) << '\n';
    std::cout << "Alignment of std::stringstream = " << std::alignment_of_v<std::stringstream> << "\n\n\n";
}

template <typename... Args>
void printBold(Args&&... args) {
    std::cout << bold;
    (std::cout << ... << args);
    std::cout << reset;
}

template <typename... Args>
void printItalics(Args&&... args) {
    std::cout << italic;
    (std::cout << ... << args);
    std::cout << reset;
}

template <typename... Args>
void printBoldItalics(Args&&... args) {
    std::cout << boldItalic;
    (std::cout << ... << args);
    std::cout << reset;
}

void ostringstreamExample() {
    std::ostringstream oss;
    oss << "Temperature: " << 72.5 << 'F';

    // This is incorrect: You can only stream data into the std::ostringstream object
    // std::string data;
    // oss >> data;

    printBold("std::ostringstream example:\n");
    printItalics(oss.str(), "\n\n");
}

void istringstreamExample() {
    printBold("std::istringstream example:\n");

    std::string record = "John 25 190.5";
    std::istringstream iss{record};

    std::string name;
    int age;
    double height;

    if (iss >> name >> age >> height) {
        printItalics(name, " is ", age, " years old with a height of ", height, " cm\n\n");
    } else {
        printBoldItalics("Failed to extract from string stream\n\n");
    }
}

void stringstreamExample() {
    printBold("std::stringstream example:\n");

    std::stringstream ss;
    ss << "100 200";

    int a, b;
    if (ss >> a >> b) {
        printItalics("Sum of a and b: ", (a + b), "\n\n");
    } else {
        printBoldItalics("Failed to extract from string stream\n\n");
    }
}

int main() {
    sizeAndAlignments();

    ostringstreamExample();
    istringstreamExample();
    stringstreamExample();
}
