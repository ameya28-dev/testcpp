#include <fstream>
#include <iostream>
#include <vector>

int main() {
    std::ifstream file("main.cpp");
    std::vector<std::string> data;
    std::string input;
    while (file >> input) {
        data.push_back(input);
    }

    file.close();

    std::cout << data.size() << std::endl;
    for (std::string& v : data) {
        std::cout << v << std::endl;
    }
}