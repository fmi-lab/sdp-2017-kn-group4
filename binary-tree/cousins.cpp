#include "binary-tree.cpp"

bool member(BinaryTree<int>::Position root, int u) {
  return root && (*root == u || member(root.left(), u) || member(root.right(), u));
}

int successors(BinaryTree<int>::Position root) {
  if (!root) {
    return 0;
  }

  int result = 0;
  if (root.left()) {
    result += 1 + successors(root.left());
  }

  if (root.right()) {
    result += 1 + successors(root.right());
  }

  return result;
}


int cousins(BinaryTree<int>::Position root, int u) {
  if (!root ||
      *root == u ||
      (root.left() && *root.left() == u) ||
      (root.right() && *root.right() == u)) {
    return 0;
  }

  if (member(root.left(), u)) {
    return successors(root.right()) + cousins(root.left(), u);
  }

  if (member(root.right(), u)) {
    return successors(root.left()) + cousins(root.right(), u);
  }

  return 0;
}
