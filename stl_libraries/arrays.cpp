#include <array>
#include <string>
// using namespace std;

int main(){
    std::array<int, 5> a1 {{3,4,5,1,2}};
    std::array<int, 5> a2 = {1,2,3,4,5};
    std::array<std::string, 2> a3 = {std::string("a"), "b"};

    return 0;
}