// https://leetcode-cn.com/problems/sort-list/
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

ListNode* sort_list_merge_inplace(ListNode* head) {
  ListNode *h, *h1, *h2, *pre, *res;
  //利用h找到该次归并的下一组起点，h1为当前归并组的左起点，h2为右起点
  // pre作为每次归并的虚设头结点，res为最终结果的虚设头结点
  int len = 0;
  h = head;

  while (h) {  //计算链表长度
    len++;
    h = h->next;
  }

  int curr_len = 1;  //当前归并目标的长度，当=length时归并结束
  res = new ListNode(0);
  res->next = head;

  while (curr_len < len) {
    pre = res;
    h = pre->next;

    while (h) {  //当前长度的归并过程，h为空说明所有结点都遍历完成
      int i = curr_len;  //寻找左起点和右起点
      h1 = h;            //左起点
      while (i > 0 && h) {
        i--;
        h = h->next;
      }
      if (i > 0)
        break;  //若由于h为空退出循环，即未找到右起点就已经无剩余结点，那么归并完成

      h2 = h;  //右起点
      i = curr_len;
      int num2 = 0;

      while (i > 0 && h) {  //将h移动到该次归并下一组的起点
        i--;
        h = h->next;
        num2++;
      }
      int num1 = curr_len;

      while (num1 > 0 && num2 > 0) {  //归并
        if (h1->val <= h2->val) {
          pre->next = h1;
          h1 = h1->next;
          num1--;
        } else {
          pre->next = h2;
          h2 = h2->next;
          num2--;
        }
        pre = pre->next;
      }

      if (num1 > 0)
        pre->next = h1;
      else if (num2 > 0)
        pre->next = h2;

      while (num1 > 0 || num2 > 0) {  //移动到该组末尾
        pre = pre->next;
        num1--;
        num2--;
      }

      pre->next = h;  //连接下一组的起点
    }
    curr_len *= 2;
  }

  return res->next;
}

int main() {
  auto list = build_list({4, 2, 1, 3});
  std::cout << sort_list_merge(list);

  auto list1 = build_list({4, 2, 1, 1, 1, 1, 3, 2, 1, 0, -1});
  std::cout << sort_list_quick(list1);

  auto list2 = generate_random(0, 100, 200);
  auto list3 = list2;
  // auto dt0 = benchmark([&]() { sort_list_quick(list2); });
  auto dt0 = benchmark([&]() { sort_list_merge_inplace(list2); });
  auto dt1 = benchmark([&]() { sort_list_merge(list3); });

  // std::cout << "quick time elapsed: " << dt0 << "ms" << std::endl;
  std::cout << "merge inplace time elapsed: " << dt0 << "ms" << std::endl;
  std::cout << "merge time elapsed: " << dt1 << "ms" << std::endl;
}
