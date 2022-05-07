#include <iostream>
#include <vector>

#include "rbtree.h"

int main() {
  std::cout << "test red black tree." << std::endl;
  std::vector<int> arr = {1, 3, 8, 12, 16, 19, 26, 5, 10, 18, 24, 13};

  RBTree<int> rbtree;
  for (const auto& a : arr) rbtree.insert(a);
  rbtree.travsal();
  std::cout << rbtree.height() << std::endl;
  return 0;
}
