#include <iostream>
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

std::ostream& operator<<(std::ostream& os, ListNode* head) {
  while (head) {
    os << head->val << " ";
    head = head->next;
  }
  std::cout << std::endl;
  return os;
}
