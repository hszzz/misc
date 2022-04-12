#include <cassert>
#include <chrono>
#include <iostream>
#include <vector>

#include "sorts.h"

void debug(const std::vector<int>& array) {
  for (const auto& item : array) std::cout << item << " ";
  std::cout << std::endl;
}

std::vector<int> generate_random_vector(const int min, const int max,
                                        const size_t n, const int seed = 0) {
  assert(n > 0);

  std::vector<int> res(n);
  srand(seed);
  for (size_t i = 0; i < n; ++i) {
    res[i] = rand() % (max - min) + min;
  }

  return res;
}

template <typename Func>
void benchmark(const Func& func) {
  auto t0 = std::chrono::steady_clock::now();
  func();
  auto t1 = std::chrono::steady_clock::now();
  auto dt = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0);
  std::cout << "time elapsed: " << dt.count() << std::endl;
}

int main() {
  std::vector<int> array = {3, 2, 1, 2, 1, 3, 5, 2, 1};
  debug(array);
  sort::counting_sort(array.begin(), array.end());
  debug(array);
  return 0;
}
