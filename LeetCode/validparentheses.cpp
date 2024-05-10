#include <unordered_map>
#include <stack>
#include <string>
#include <iostream>
using namespace std;

class Solution {
public:
    bool isValid(string s) {
        unordered_map<char, char> map = {{'}','{'},{')','('},{']','['}};
        stack<char> st{};
        for(char c:s){
            if(map.find(c) != map.end()){
                st.push(c);
            }
            else{
                if(!st.empty() && map[c] != st.top()){
                    return false;
                }
                else {
                    return true;
                }
            }
        }
        return st.empty();
    }
};

int main(){
    Solution sol;
    cout << sol.isValid("()[]{}");
    return 0;
}