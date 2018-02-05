#include "UnitTestFramework.h"

std::string treeToString (const Node *r)
{
  if (r == nullptr)
    {
      return "()";
    }

  return "(" +
    treeToString (r->left) +
    r->data +
    treeToString(r->right) +
    ")";

}

TEST_CASE("Problem1", Problem1_Empty) {
  Assert::AreEqual(buildTree(""), nullptr);
}

TEST_CASE("Problem1", Problem1_SingleChar) {
  Assert::AreEqual(treeToString(buildTree("x")),
                   std::string("(()x())"));
}

TEST_CASE("Problem1", Problem1_TwoChars) {
  Assert::AreEqual(treeToString(buildTree("xy")),
                   std::string("((()x())y())"));
}

TEST_CASE("Problem1", Problem1_Example) {
  Assert::AreEqual(treeToString(buildTree("abcdef")),
                   std::string("(((()a())b(()c()))d((()e())f()))"));
}

TEST_CASE("Problem1", Problem1_FullTree) {
  Assert::AreEqual(treeToString(buildTree("abcdefg")),
                   std::string("(((()a())b(()c()))d((()e())f(()g())))"));
}

TEST_CASE("Problem1", Problem1_LeftTree) {
  Assert::AreEqual(treeToString(buildTree("abcdefgh")),
                   std::string("((((()a())b())c(()d()))e((()f())g(()h())))"));
}
