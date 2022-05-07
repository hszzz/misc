#ifndef RBTREE_H
#define RBTREE_H

#include <cmath>
#include <iomanip>
#include <iostream>
#include <queue>

// hszzz at 2022/05/02

// 1. 根节点为黑色
// 2. 相邻的节点不能同时为红色
// 3. 每个节点从自身到各个能到达的叶子结点的所有路径中的黑色节点数量相等
// 4. 红节点只能作为左子节点存在（这是左偏红黑树特有的要求）

namespace detail {

enum RBColor {
  kBlack = 0,
  kRed,
};

template <class T>
struct RBTreeNode {
  RBColor color = kBlack;
  RBTreeNode* left = nullptr;
  RBTreeNode* right = nullptr;
  RBTreeNode* parent = nullptr;

  RBTreeNode(T val) : value(val) {}
  RBTreeNode(T val, RBColor color) : value(val), color(color) {}
  RBTreeNode(T val, RBColor color, RBTreeNode* parent)
      : value(val), color(color), parent(parent) {}

  T value;
};

}  // namespace detail

template <class T>
class RBTree {
 public:
  using Node = detail::RBTreeNode<T>;

  RBTree() : root_(nullptr), nil_(new Node(-1)), size_(0) { root_ = nil_; }

  ~RBTree() {
    destory(root_);
    delete nil_;
  }

  void insert(const T& val) {
    Node* node = create_node(val);
    Node* parent = nil_;
    Node* temp = root_;

    while (temp != nil_) {
      parent = temp;
      if (val < temp->value)
        temp = temp->left;
      else
        temp = temp->right;
    }

    node->parent = parent;

    if (parent == nil_)
      root_ = node;
    else if (val < parent->value)
      parent->left = node;
    else
      parent->right = node;

    insert_fixup(node);
  }

  void travsal() {
    travsal(root_);
    std::cout << std::endl;
  }

  int height() const { return height(root_); }

 private:
  Node* create_node(T val) {
    Node* node = new Node(val, detail::RBColor::kRed);
    node->parent = nil_;
    node->left = nil_;
    node->right = nil_;
    return node;
  }

  void rotate_left(Node* node) {
    Node* right = node->right;
    node->right = right->left;

    if (right->left != nil_) {
      right->left->parent = node;
      right->parent = node->parent;
    }

    if (node->parent == nil_)
      root_ = right;
    else if (node->parent->left == node)
      node->parent->left = right;
    else
      node->parent->right = right;

    right->left = node;
    node->parent = right;
  }

  void rotate_right(Node* node) {
    Node* left = node->left;
    node->left = left->right;

    if (left->right != nil_) {
      left->right->parent = node;
      left->parent = node->parent;
    }

    if (node->parent == nil_)
      root_ = left;
    else if (node->parent->left == node)
      node->parent->left = left;
    else
      node->parent->right = left;

    left->right = node;
    node->parent = left;
  }

  void insert_fixup(Node* node) {
    while (node->parent->color == detail::RBColor::kRed) {
      if (node->parent == node->parent->parent->left) {
        Node* tmp = node->parent->parent->right;
        if (tmp->color == detail::RBColor::kRed) {
          node->parent->color = detail::RBColor::kBlack;
          tmp->color = detail::RBColor::kBlack;
          node->parent->parent->color = detail::RBColor::kRed;

          node = node->parent->parent;
        } else if (node == node->parent->right) {
          node = node->parent;
          rotate_left(node);
        } else {
          node->parent->color = detail::RBColor::kBlack;
          node->parent->parent->color = detail::RBColor::kRed;
          rotate_right(node->parent->parent);
        }
      } else {
        Node* tmp = node->parent->parent->left;

        if (tmp->color == detail::RBColor::kRed) {
          node->parent->color = detail::RBColor::kBlack;
          tmp->color = detail::RBColor::kBlack;

          node->parent->parent->color = detail::RBColor::kRed;
          node = node->parent->parent;
        } else if (node == node->parent->left) {
          node = node->parent;
          rotate_right(node);
        } else {
          node->parent->color = detail::RBColor::kBlack;
          node->parent->parent->color = detail::RBColor::kRed;
          rotate_left(node->parent->parent);
        }
      }
    }
    root_->color = detail::RBColor::kBlack;
  }

  void travsal(detail::RBTreeNode<T>* root) {
    std::queue<std::pair<int, detail::RBTreeNode<T>*>> queue;
    queue.push({std::pow(2, height() - 1) / 2 * 3, root});
    int h = height();

    while (!queue.empty()) {
      int cnt = queue.size();
      int before = 0;
      while (cnt--) {
        detail::RBTreeNode<T>* node = queue.front().second;
        int space = queue.front().first;
        std::cout << std::setw(space - before) << node->value;
        before = space;

        if (node->left != nil_) queue.push({space - h, node->left});
        if (node->right != nil_) queue.push({space + h, node->right});
        queue.pop();
        h--;
      }
      before = 0;
      std::cout << std::endl;
    }
  }

  int height(Node* node) const {
    if (node == nil_) return 0;
    return std::max(height(node->left), height(node->right)) + 1;
  }

  void destory(Node* root) {
    if (root == nil_) return;
    destory(root->left);
    destory(root->right);
    delete root;
  }

 private:
  Node* root_ = nullptr;
  Node* nil_ = nullptr;
  size_t size_ = 0;
};

#endif  // RBTREE_H
