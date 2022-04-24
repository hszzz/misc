// https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list-ii/
#include <iostream>
#include <vector>

#include "leetcode_linkedlist.h"

/**
struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};
*/

ListNode* deleteDuplicate(ListNode* head) {
  ListNode dummy(-1, head);
  ListNode* cur = &dummy;

  while (cur->next && cur->next->next) {
    if (cur->next->val == cur->next->next->val) {
      int x = cur->next->val;
      while (cur->next && cur->next->val == x) {
        cur->next = cur->next->next;
      }
    } else {
      cur = cur->next;
    }
  }

  return dummy.next;
}

int main() {
  ListNode* list = build_list({1, 1, 1, 2, 3});
  std::cout << list;
  list = deleteDuplicate(list);
  std::cout << list;
}
