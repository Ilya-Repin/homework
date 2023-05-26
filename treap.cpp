#include <iostream>
#include <vector>

struct Node {
  int key = 0;
  int priority = 0;
  size_t order_num = 0;

  Node *left = nullptr;
  Node *right = nullptr;
  Node *parent = nullptr;

  Node(int k, int p, int on) : key(k), priority(p), order_num(on) {
  }
};

void Build(std::vector<std::pair<int, int>> &values, std::vector<Node *> &result) {
  Node *root = nullptr;
  Node *last_inserted = nullptr;
  size_t num = 1;

  for (auto value : values) {
    Node *new_node = new Node(value.first, value.second, num++);
    Node *curr = last_inserted;

    result.push_back(new_node);

    while (curr != nullptr && value.second < curr->priority) {
      curr = curr->parent;
    }

    if (curr == nullptr) {
      new_node->left = root;

      if (root != nullptr) {
        root->parent = new_node;
      }

      root = new_node;
    } else {
      new_node->left = curr->right;

      if (curr->right != nullptr) {
        curr->right->parent = new_node;
      }

      curr->right = new_node;
      new_node->parent = curr;
    }

    last_inserted = new_node;
  }
}

int main() {
  int n;
  std::cin >> n;
  std::vector<std::pair<int, int>> elems(n);

  for (int i = 0; i < n; ++i) {
    std::cin >> elems[i].first >> elems[i].second;
  }

  std::vector<Node *> result;
  Build(elems, result);

  std::cout << "YES\n";
  for (auto x : result) {
    std::cout << (x->parent == nullptr ? 0 : x->parent->order_num) << " ";
    std::cout << (x->left == nullptr ? 0 : x->left->order_num) << " ";
    std::cout << (x->right == nullptr ? 0 : x->right->order_num) << "\n";
  }

  for (auto node : result) {
    delete node;
  }
  result.clear();

  return 0;
}