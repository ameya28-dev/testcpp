#include <string>
#include <unordered_map>
#include <iostream>

int main() {
    std::unordered_map<int, std::string> map{
        {1, "Hello!!"},
        {2, "Is there anybody in there??"},
        {3, "Just nod if you can here me...."},
        {4, "Is there any one at home??"}};

    for(auto& [key, value]: map) {
        std::cout << key << ": " << value << '\n';
    }
}