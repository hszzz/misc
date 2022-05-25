#include <iostream>

#include "leetcode_linkedlist.h"

ListNode* reverseLinkedList(ListNode* list) {
  if (list == nullptr || list->next == nullptr) return list;
  ListNode* node = reverseLinkedList(list->next);
  list->next->next = list;
  list->next = nullptr;
  return node;
}

ListNode* reverseLinkedList1(ListNode* list) {
  if (list == nullptr || list->next == nullptr) return list;

  ListNode* pre = nullptr;
  ListNode* cur = list;

  while (cur) {
    auto node = cur->next;
    cur->next = pre;

    pre = cur;
    cur = node;
  }

  return pre;
}

int main() {
  auto list = build_list({1, 2, 3, 4, 5});
  std::cout << list;
  auto list1 = reverseLinkedList(list);
  std::cout << list1;

  auto list2 = build_list({1, 2, 3, 4, 5});
  std::cout << list2;
  auto list3 = reverseLinkedList1(list2);
  std::cout << list3;
}

