#include <unordered_map>
#include <stack>
#include <string>
#include <iostream>
// using namespace std;

class Solution {
public:
    bool isValid(std::string s) {
        std::unordered_map<char, char> map = {{'}','{'},{')','('},{']','['}};
        std::stack<char> st{};
        for(char c:s){
            if(map.find(c) == map.end()){
                st.push(c);
            }
            else{
                if(!st.empty() && map[c] != st.top()){
                    return false;
                }
                st.pop();
            }
        }
        return st.empty();
    }
};

int main() {
    Solution sol;
    std::cout << sol.isValid("(){[}]");
    return 0;
}