#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>
// using namespace std;

// class Solution {
// public:
//     vector<vector<string>> groupAnagrams(vector<string>& strs) {
//         unordered_map<vector<int>,vector<string>> hashmap;
//         for(string str:strs){
//             vector<int> count(26, 0);
//             for(char c : str){
//                 count[c-'a']++;
//             }
//             hashmap[count].push_back(str);
//         }

//         vector<vector<string>> res {};
//         for(auto x:hashmap){
//             res.push_back(x.second);
//         }

//         return res;
//     }
// };

int main(){
    int x = 'a'+1;
    std::cout << x << '\n';
    std::cout << (char) x;

//    std::stringstream ss;
}
