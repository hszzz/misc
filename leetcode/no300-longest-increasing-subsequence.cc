#include <iostream>
#include <vector>

// O(n^2) O(n)
class Solution {
 public:
  int lengthOfLIS(std::vector<int>& nums) {
    int res = 0;
    std::vector<int> dp(nums.size(), 1);

    for (int i = 0; i < nums.size(); ++i) {
      for (int j = 0; j < i; ++j) {
        if (nums[j] > nums[i]) dp[i] = std::max(dp[i], dp[j] + 1);
      }
      res = std::max(res, dp[i]);
    }

    return res;
  }
};

int main() {
  Solution solution;
  std::vector<int> array = {10, 9, 2, 5, 3, 7, 101, 18};
  std::cout << solution.lengthOfLIS(array) << std::endl;
}
