#include <cmath>
#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<int> sortedSquares(std::vector<int>& nums) {
        std::vector<int> res(nums.size());
        size_t left = 0, right  = nums.size() - 1, index = nums.size() - 1;
        while (left  <=  right) {
            if (std::abs(nums[right]) > std::abs(nums[left])) {
                res[index] = nums[right] * nums[right];
                right--;
            } else {
                res[index] = nums[left] * nums [left];
                left++;
            }

            index--;
        }


        return res;
    }

    std::vector<int> sortedSquares2(std::vector<int>& nums) {
        std::vector<int> res(nums.size());
        std::vector<int>::const_iterator left = nums.begin(), right  = nums.end() - 1;
        std::vector<int>::iterator index = res.end() - 1;
        while (left  <=  right) {
            if (std::abs(*right) > std::abs(*left)) {
                *index = std::pow(*right, 2);
                right--;
            } else {
                *index = std::pow(*left, 2);
                left++;
            }

            index--;
        }


        return res;
    }
};


int main(int argc, char const *argv[])
{
    Solution s;
    std::vector<int> v{ -4, -1, 0, 3, 10};
    auto res = s.sortedSquares2(v);
    for (int i : res) {
        std::cout << i << '\t';
    }
    return 0;
}