#include <algorithm>
#include <iostream>
#include <vector>

bool binarySearch(std::vector<int> nums, int target) {
  int l = 0, r = nums.size() - 1;

  while (l <= r) {
    int m = l + (r - l) / 2;
    if (nums[m] == target) {
      return true;
    } else if (nums[m] > target) {
      r = m - 1;
    } else {
      l = m + 1;
    }
  }
  return false;
}

int main() {
  std::vector<int> nums{1, 2, 3, 4, 5};
  std::cout << binarySearch(nums, 5);
  return 0;
}
