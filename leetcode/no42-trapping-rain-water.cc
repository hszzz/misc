#include <cassert>
#include <iostream>
#include <stack>
#include <vector>

class Solution {
 public:
  // dp
  int trap(std::vector<int>& height) {
    size_t len = height.size();
    if (len == 0) return 0;

    std::vector<int> left_max(len, 0);
    left_max[0] = height[0];
    for (size_t i = 1; i < len; ++i) {
      left_max[i] = std::max(left_max[i - 1], height[i]);
    }

    std::vector<int> right_max(len, 0);
    right_max[len - 1] = height[len - 1];
    for (int i = len - 2; i >= 0; --i) {
      right_max[i] = std::max(right_max[i + 1], height[i]);
    }

    int res = 0;
    for (size_t i = 0; i < len; ++i) {
      res += std::min(left_max[i], right_max[i]) - height[i];
    }

    return res;
  }

  // stack
  int trap1(std::vector<int>& height) {
    std::stack<int> stack;
    int res = 0;

    for (size_t i = 0; i < height.size(); ++i) {
      while (!stack.empty() && height[stack.top()] < height[i]) {
        int bottom = stack.top();
        stack.pop();

        while (!stack.empty() && height[stack.top()] == height[bottom])
          stack.pop();

        if (!stack.empty())
          res += (std::min(height[stack.top()], height[i]) - height[bottom]) *
                 (i - stack.top() - 1);
      }
      stack.push(i);
    }

    return res;
  }
};

int main() {
  Solution solution;
  // dp
  std::vector<int> array = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};  // 6
  std::vector<int> array1 = {4, 2, 0, 3, 2, 5};                   // 9

  assert(solution.trap(array) == 6);
  std::cout << solution.trap(array) << std::endl;

  assert(solution.trap(array1) == 9);
  std::cout << solution.trap(array1) << std::endl;

  // stack
  assert(solution.trap1(array) == 6);
  std::cout << solution.trap1(array) << std::endl;

  assert(solution.trap1(array1) == 9);
  std::cout << solution.trap1(array1) << std::endl;
}
