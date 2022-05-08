#include <algorithm>
#include <iostream>
#include <vector>

// 暴力
std::vector<int> sortedSquares(std::vector<int>& nums) {
  for (auto& num : nums) num *= num;
  std::sort(nums.begin(), nums.end());
  return nums;
}

// 双指针
std::vector<int> sortedSquares1(std::vector<int>& nums) {
  std::vector<int> res(nums.size());
  int left = 0;
  int right = nums.size() - 1;
  int k = right;

  while (left <= right) {
    if (nums[left] * nums[left] < nums[right] * nums[right]) {
      res[k--] = nums[right] * nums[right];
      --right;
    } else {
      res[k--] = nums[left] * nums[left];
      ++left;
    }
  }

  return res;
}

void debug(const std::vector<int>& nums) {
  for (const auto& num : nums) std::cout << num << " ";
  std::cout << std::endl;
}

int main() {
  std::vector<int> nums = {-4, -1, 0, 3, 10};
  debug(nums);
  sortedSquares(nums);
  debug(nums);

  std::vector<int> nums1 = {-4, -1, 0, 3, 10};
  debug(nums1);
  auto n = sortedSquares1(nums1);
  debug(n);
}
