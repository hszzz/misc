#include <iostream>

#include "leetcode_linkedlist.h"

ListNode* swapPairs(ListNode* head) {
  ListNode dummy(0, head);

  ListNode* cur = &dummy;

  while (cur->next && cur->next->next) {
    ListNode* begin = cur->next;
    ListNode* end = cur->next->next;

    begin->next = end->next;
    cur->next = end;
    end->next = begin;

    cur = cur->next->next;
  }

  return dummy.next;
}

int main() {
  auto list = build_list({1, 2, 3, 4});
  std::cout << list;
  auto list1 = swapPairs(list);
  std::cout << list1;

  auto list2 = generate_random(1, 10, 9);
  std::cout << list2;
  auto list3 = swapPairs(list2);
  std::cout << list3;
}
