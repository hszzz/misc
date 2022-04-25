#include <iostream>
#include <random>
#include <vector>

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

ListNode* build_list(const std::vector<int>& list) {
  ListNode dummy;
  ListNode* cur = &dummy;

  for (auto num : list) {
    cur->next = new ListNode(num);
    cur = cur->next;
  }

  return dummy.next;
}

void destroy_list(ListNode* head) {
  while (head) {
    auto node = head;
    head = head->next;

    delete node;
  }
}

ListNode* generate_random(int min, int max, size_t len) {
  ListNode dummy;
  ListNode* cur = &dummy;

  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> digst(min, max);

  for (size_t i = 0; i < len; ++i) {
    cur->next = new ListNode(digst(rng));
    cur = cur->next;
  }

  return dummy.next;
}

std::ostream& operator<<(std::ostream& os, ListNode* head) {
  while (head) {
    os << head->val << " ";
    head = head->next;
  }
  os << std::endl;
  return os;
}
