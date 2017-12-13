#include <iostream>

template <typename T>
class BinaryTree {
  struct Node {
    T data;
    Node* left;
    Node* right;

    explicit Node(T const& data, Node* left = nullptr, Node* right = nullptr)
      : data(data), left(left), right(right) {}
  };

  Node* root;

  Node* copy(Node* node) {
    if (node == nullptr) {
      return nullptr;
    }

    return new Node(node->data, copy(node->left), copy(node->right));
  }

  void erase(Node* node) {
    if (node == nullptr) {
      return;
    }

    erase(node->left);
    erase(node->right);
    delete node;
  }

  explicit BinaryTree(Node* root): root(copy(root)) {}

public:

  class Position {
    Node*& p;

  public:
    explicit Position(Node*& p): p(p) {};

    explicit operator bool() const {
      return p != nullptr;
    }

    bool operator!() {
      return !(bool)*this;
    }

    T operator*() const {
      return p->data;
    }

    Position left() const {
      return Position(p->left);
    }

    Position right() const {
      return Position(p->right);
    }
  };

  BinaryTree(): root(nullptr) {}

  BinaryTree(T const& data, BinaryTree left, BinaryTree right) {
    root = new Node(data);
    std::swap(root->left, left.root);
    std::swap(root->right, right.root);
  }

  BinaryTree(BinaryTree&& other) noexcept: BinaryTree() {
    std::swap(root, other.root);
  }

  BinaryTree(BinaryTree const& other): root(copy(other.root)) {}

  BinaryTree& operator=(BinaryTree other) {
    std::swap(root, other.root);
    return *this;
  }

  ~BinaryTree() {
    erase(root);
  }

  Position get_root() {
    return Position(root);
  }

  BinaryTree left() const {
    return BinaryTree(root->left);
  }

  BinaryTree right() const {
    return BinaryTree(root->right);
  }

  bool empty() const {
    return root == nullptr;
  }
};

template <typename T>
using P = typename BinaryTree<T>::Position;

template <typename T>
void print(BinaryTree<T>& tree) {
  print<T>(tree.get_root());
}

template <typename T>
void print(P<T> p) {
  if (!p) {
    return;
  }

  std::cout << *p << '\n';

  print<T>(p.left());
  print<T>(p.right());
}

int main() {
  BinaryTree<int> tree(
    1,
    BinaryTree<int>(
      2,
      BinaryTree<int>(3, BinaryTree<int>(), BinaryTree<int>()),
      BinaryTree<int>(4, BinaryTree<int>(), BinaryTree<int>())
    ),
    BinaryTree<int>(
      5,
      BinaryTree<int>(),
      BinaryTree<int>(6, BinaryTree<int>(), BinaryTree<int>())
    )
  );

  print(tree);

  BinaryTree<int> e;

  BinaryTree<int> s11(3, e, e);
  BinaryTree<int> s12(4, e, e);

  s11 = std::move(s12);

  print(s11);
  print(s12);

  return 0;
}