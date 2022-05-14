#include <climits>
#include <iostream>
#include <vector>

int minSubArray(int target, std::vector<int> &nums) {
  int res = INT_MAX;
  int current = 0;

  for (int i = 0; i < nums.size(); ++i) {
    int sum = 0;
    for (int j = i; j < nums.size(); ++j) {
      current++;
      sum += nums[j];
      if (sum >= target) {
        res = std::min(res, current);
        current = 0;
        break;
      }
    }
  }

  return res == INT_MAX ? 0 : res;
}

int minSubArray1(int target, std::vector<int>& nums) {
  int res = INT_MAX;

  int sum = 0;
  int left = 0;
  int right = 0;

  while (right < nums.size()) {
    sum += nums[right];

    while (sum >= target) {
      res = std::min(res, right - left + 1);
      sum -= nums[left++];
    }

    right++;
  }

  return res == INT_MAX ? 0 : res;
}

int main() {
  std::vector<int> nums1 = {2, 3, 1, 2, 4, 3};
  std::vector<int> nums2 = {1, 4, 4};
  std::vector<int> nums3 = {1, 1, 1, 1, 1, 1, 1, 1};

  std::cout << minSubArray(7, nums1) << std::endl;
  std::cout << minSubArray(4, nums2) << std::endl;
  std::cout << minSubArray(11, nums3) << std::endl;

  std::cout << minSubArray1(7, nums1) << std::endl;
  std::cout << minSubArray1(4, nums2) << std::endl;
  std::cout << minSubArray1(11, nums3) << std::endl;

  return 0;
}
