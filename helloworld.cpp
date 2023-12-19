#include <iostream>
#include <string>
#include <vector>

using std::cout, std::endl, std::string, std::vector, std::size_t, std::cin;

int main(){
    string x;
    cout << "Enter your name:" << '\t';
    cin >> x;
    cout << '\n' << "Hello World!" << x << '\n';
    return 0;
}
