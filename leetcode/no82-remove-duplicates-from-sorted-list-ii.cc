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

ListNode* deleteDuplicate1(ListNode* head) {
  if (head == nullptr || head->next == nullptr) return head;

  if (head->val != head->next->val) {
    deleteDuplicate1(head->next);
  } else {
    ListNode* skip = head->next;
    while (skip && head->val == skip->val) {
      skip = skip->next;
    }
    return deleteDuplicate1(skip);
  }

  return head;
}

int main() {
  ListNode* list = build_list({1, 1, 1, 2, 3});
  std::cout << list;
  list = deleteDuplicate(list);
  std::cout << list;
  ListNode* list1 = build_list({1, 1, 1, 2, 3});
  list1 = deleteDuplicate1(list1);
  std::cout << list1;
}
