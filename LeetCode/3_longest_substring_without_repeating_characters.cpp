#include <string>
#include <unordered_set>
#include <cmath>
#include <unordered_map>
#include <iostream>

class Solution {
public:
    int lengthOfLongestSubstring(std::string s) {
        std::unordered_set<char> charSet;
        int left  = 0;
        int length = 0;
        for (int right = 0; right < s.length(); right++) {
            while (charSet.find(s[right]) != charSet.end()) {
                charSet.erase(s[left]);
                left++;
            }
            charSet.insert(s[right]);
            length = std::max(length, right - left + 1);
        }
        return length;
    }

    int lengthOfLongestSubstringWithHashMap(const std::string& s) {
        std::unordered_map<char, int> char_map;
        int left = 0;
        int max_length = 0;
        for (int right = 0; right < s.length(); right++) {
            if (char_map.find(s[right]) == char_map.end()) {
                char_map.emplace(s[right], right);
            } else {
                left = char_map.at(s[right]) + 1;
                char_map[s[right]] = right;
            }
            max_length = std::max(max_length, right - left + 1);
        }
        return max_length;
    }
};

int main() {
    Solution sol;

    std::cout << sol.lengthOfLongestSubstringWithHashMap("abba") << '\n';
    std::cout << sol.lengthOfLongestSubstring("pwwska") << '\n';
}