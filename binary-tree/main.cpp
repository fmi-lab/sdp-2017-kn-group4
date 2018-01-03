#include <iostream>
#include "cousins.cpp"

int main() {
  BinaryTree<int> tree(
    1,
    BinaryTree<int>(2,
                    BinaryTree<int>(4,
                                    BinaryTree<int>(8,
                                                    BinaryTree<int>(13),
                                                    BinaryTree<int>(14)),
                                    BinaryTree<int>(9)),
                    BinaryTree<int>(5,
                                    BinaryTree<int>(),
                                    BinaryTree<int>(10,
                                                    BinaryTree<int>(15),
                                                    BinaryTree<int>(16)))),
    BinaryTree<int>(3,
                    BinaryTree<int>(6),
                    BinaryTree<int>(7,
                                    BinaryTree<int>(11),
                                    BinaryTree<int>(12)))
  );

  std::cout << "Cousins: " << cousins(tree.get_root(), 10) << '\n';

  return 0;
}
