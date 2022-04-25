#include <chrono>

template <typename Func>
long benchmark(const Func& func) {
  auto t0 = std::chrono::steady_clock::now();
  func();
  auto t1 = std::chrono::steady_clock::now();
  auto dt = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0);
  return dt.count();
}
