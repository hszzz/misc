#include <iostream>

#include "leetcode_linkedlist.h"

ListNode* removeNthFromEnd(ListNode* head, int n) {
  ListNode dummy(-1, head);

  ListNode* slow = &dummy;
  ListNode* fast = &dummy;

  while (n-- && fast) {
    fast = fast->next;
  }

  fast = fast->next;
  while (fast) {
    fast = fast->next;
    slow = slow->next;
  }

  ListNode* toDel = slow->next;
  slow->next = slow->next->next;
  delete toDel;

  return dummy.next;
}

int main() {
  auto list = build_list({1, 2, 3, 4, 5, 6, 7, 8, 9});
  std::cout << list;
  auto list1 = removeNthFromEnd(list, 3);
  std::cout << list1;
}
