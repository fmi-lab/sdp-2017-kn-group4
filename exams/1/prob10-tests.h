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
std::stringstream t4s  ("(2 (1 (1 () ()) (0 () ())) (0 () ()))");

Node const * const t0 = nullptr;
Node const * const t00 = nullptr;
Node const * const t1 = parseTree (t1s);
Node const * const t2 = parseTree (t2s);
Node const * const t3 = parseTree (t3s);
Node const * const t4 = parseTree (t4s);


TEST_CASE("Problem10", EmptyCounterTrees) {
  Assert::IsTrue(counter(t0, t00));
}

TEST_CASE("Problem10", EmptyNonEmptyNonCounterTrees) {
  Assert::IsFalse(counter(t0, t1));
}

TEST_CASE("Problem10", CounterTrees) {
  Assert::IsTrue(counter(t1, t3));
}

TEST_CASE("Problem10", NonIsomorphicTrees) {
  Assert::IsFalse(counter(t1, t2));
}

TEST_CASE("Problem10", IsomorphicNoncounterTrees) {
  Assert::IsFalse(counter(t2, t4));
}

