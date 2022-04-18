#include <vector>

class Solution {
 public:
  ListNode* mergeLists(const std::vector<ListNode*>& lists) {
    return merge(lists, 0, lists.size() - 1);
  }

 private:
  ListNode* merge(ListNode* l1, ListNode* l2) {
    ListNode dummy;
    ListNode* cur = dummy.next;

    while (l1 && l2) {
      if (l1->val < l2->val) {
        cur->next = l1;
        l1 = l1->next;
      } else {
        cur->next = l2;
        l2 = l2->next;
      }
      cur = cur->next;
    }

    return dummy.next;
  }

  ListNode* merge(std::vector<ListNode*> lists, int left, int right) {
    if (left == right) return lists[left];
    if (left > right) return nullptr;
    int mid = (left + right) / 2;
    return merge(merge(lists, left, mid), merge(lists, mid + 1, right));
  }
};
