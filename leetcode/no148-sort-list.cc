#include "benchmark.h"
#include "leetcode_linkedlist.h"

ListNode* merge(ListNode* l1, ListNode* l2) {
  ListNode dummy;
  ListNode* cur = &dummy;

  while (l1 && l2) {
    ListNode*& link = l1->val > l2->val ? l2 : l1;
    cur->next = link;
    link = link->next;
    cur = cur->next;
  }
  cur->next = l1 ? l1 : l2;

  return dummy.next;
}

ListNode* sort_list_merge(ListNode* head) {
  if (!head || !head->next) return head;
  auto slow = head;
  auto fast = head;

  while (fast->next && fast->next->next) {
    slow = slow->next;
    fast = fast->next->next;
  }

  fast = slow->next;
  slow->next = nullptr;
  return merge(sort_list_merge(head), sort_list_merge(fast));
}

ListNode* partition(ListNode* head, ListNode* tail) {
  ListNode* fast = head;
  ListNode* slow = head;
  while (fast->next != tail && fast->next->next != tail) {
    slow = slow->next;
    fast = fast->next->next;
  }
  std::swap(head->val, slow->val);

  int pv = head->val;
  ListNode* pivot = head;
  ListNode* cur = head->next;

  while (cur != nullptr) {
    if (pv > cur->val) {
      pivot = pivot->next;
      std::swap(cur->val, pivot->val);
    }
    cur = cur->next;
  }
  std::swap(head->val, pivot->val);

  return pivot;
}

void sort_list_quick(ListNode* head, ListNode* tail) {
  if (head == tail || head == nullptr || tail == nullptr) return;
  ListNode* pivot = partition(head, tail);
  sort_list_quick(head, pivot);
  sort_list_quick(pivot->next, tail);
}

ListNode* sort_list_quick(ListNode* head) {
  if (head == nullptr || head->next == nullptr) return head;

  ListNode* tail = head;
  while (tail->next) {
    tail = tail->next;
  }

  sort_list_quick(head, tail);
  return head;
}

int main() {
  auto list = build_list({4, 2, 1, 3});
  std::cout << sort_list_merge(list);

  auto list1 = build_list({4, 2, 1, 1, 1, 1, 3, 2, 1, 0, -1});
  std::cout << sort_list_quick(list1);

  auto list2 = generate_random(0, 1000000, 200000);
  auto list3 = list2;
  auto dt0 = benchmark([&]() { sort_list_quick(list2); });
  auto dt1 = benchmark([&]() { sort_list_merge(list3); });

  std::cout << "quick time elapsed: " << dt0 << "ms" << std::endl;
  std::cout << "merge time elapsed: " << dt1 << "ms" << std::endl;
}
