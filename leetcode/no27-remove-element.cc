#include <iostream>
#include <vector>

int removeElement(std::vector<int>& nums, int val) {
  size_t size = nums.size();
  for (size_t i = 0; i < size; ++i) {
    if (nums[i] == val) {
      for (size_t j = i + 1; j < size; ++j) {
        nums[j - 1] = nums[j];
      }
      i--;
      size--;
    }
  }
  return size;
}

int removeElement1(std::vector<int>& nums, int val) {
  size_t slow = 0;
  for (size_t fast = 0; fast < nums.size(); ++fast) {
    if (nums[fast] != val) nums[slow++] = nums[fast];
  }
  return slow;
}

void debug(const std::vector<int>& arr, size_t len) {
  for (size_t i = 0; i < len; ++i) std::cout << arr[i] << " ";
  std::cout << std::endl;
}

int main() {
  std::vector<int> arr = {0, 1, 2, 2, 3, 0, 4, 2};
  debug(arr, arr.size());
  auto len = removeElement(arr, 2);
  debug(arr, len);

  std::vector<int> arr1 = {0, 1, 2, 2, 3, 0, 4, 2};
  debug(arr1, arr1.size());
  auto len1 = removeElement1(arr1, 2);
  debug(arr1, len1);
}
