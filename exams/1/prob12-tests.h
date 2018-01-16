#include <cassert>
#include <sstream>

#include "UnitTestFramework.h"

Node* parseTree (std::istream& in)
{
  while (in.peek() == 32) {in.get();}
  assert (in.peek() == '(');
  in.get();

  Node *result = nullptr;

  if (in.peek() != ')')
  {

    result = new Node();
    in >> result->x;
    result->left = parseTree (in);
    result->right = parseTree (in);

  }

  assert (in.get() == ')');

  return result;
}

void printTree (const Node *t, std::ostream& out)
{
  out << '(';
  if (t != nullptr)
  {
    out << t->x << " ";
    printTree (t->left, out);
    printTree (t->right, out);
  }

  out << ')';
}

std::stringstream t1s  ("(1 (2 () ()) (3 (4 () ()) (5 () ())))");
std::stringstream t2s  ("(1 (3 (5 () ()) (4 () ())) (2 () ()))");
std::stringstream t3s  ("(2 (0 () ()) (2 (0 () ()) (0 () ())))");
std::stringstream t4s  ("(1 () ())");

Node const * const t0 = nullptr;
Node const * const t1 = parseTree (t1s);
Node const * const t2 = parseTree (t2s);
Node const * const t3 = parseTree (t3s);
Node const * const t4 = parseTree (t4s);

TEST_CASE("Problem12", LevelIterator_EmptyTreeEnd) {
  LevelIterator li = t0;
  Assert::IsTrue(li.end());
}

TEST_CASE("Problem12", LevelIterator_LeafTreeEnd) {
  LevelIterator li = t4;
  Assert::IsFalse(li.end());
  li.next();
  Assert::IsTrue(li.end());
}

TEST_CASE("Problem12", LevelIterator_LeafTreeCount) {
  LevelIterator li = t4;
  Assert::AreEqual(li.currentSum(), 1);
}

TEST_CASE("Problem12", LevelIterator_Tree1Traverse) {
  int answer[] = {1, 5, 9};
  int i = 0;
  for(LevelIterator li = t1; !li.end(); li.next(), i++)
    Assert::AreEqual(li.currentSum(), answer[i]);
  Assert::AreEqual(i, 3);
}

TEST_CASE("Problem12", LevelIterator_Tree2Traverse) {
  int answer[] = {1, 5, 9};
  int i = 0;
  for(LevelIterator li = t2; !li.end(); li.next(), i++)
    Assert::AreEqual(li.currentSum(), answer[i]);
  Assert::AreEqual(i, 3);
}

TEST_CASE("Problem12", LevelIterator_Tree3Traverse) {
  int answer[] = {2, 2, 0};
  int i = 0;
  for(LevelIterator li = t3; !li.end(); li.next(), i++)
    Assert::AreEqual(li.currentSum(), answer[i]);
  Assert::AreEqual(i, 3);
}
