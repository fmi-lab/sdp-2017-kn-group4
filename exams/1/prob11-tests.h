#include <iostream>
#include <vector>

#include "UnitTestFramework.h"

bool alwaysTrue(int) {
  return true;
}

bool alwaysFalse(int) {
  return false;
}

bool greaterThanThree(int x) {
  return x > 3;
}

Elem* buildList(std::vector<int> v) {
  Elem *start = nullptr;
  Elem** p = &start;
  for(int x : v) {
    *p = new Elem{ x, nullptr };
    p = &(*p)->next;
  }
  return start;
}

void printList(Elem* l, std::ostream& os = std::cout) {
  while (l) {
    os << l->x << ' ';
    l = l->next;
  }
  os << std::endl;
}

bool equalList(Elem* l, std::vector<int> v) {
  for (int x : v) {
    if (!l || l->x != x) return false;
    l = l->next;
  }
  return l == nullptr;
}

bool isEmpty(Elem* l) {
  return l == nullptr;
}

using vint = std::vector<int>;
vint v1{1, 7, 4, 3, 8, 8};
vint v2{1, 4, 8};
vint v3{7, 3, 8};
vint v4{4, 8};
vint v5{7, 8};
vint v6{8};
vint v7{4};

TEST_CASE("Problem11", EmptyListProject) {
  Elem const * const L = nullptr;
  Elem *L1 = new Elem{ 0, nullptr }, *L2 = new Elem{ 1, nullptr };
  project(L, alwaysTrue, L1, L2);
  Assert::AreEqual(L1, nullptr);
  Assert::AreEqual(L2, nullptr);
}

TEST_CASE("Problem11", ProjectAll) {
  Elem const * const L = buildList(v1);
  Elem *L1 = new Elem{ 0, nullptr }, *L2 = new Elem{ 1, nullptr };
  project(L, alwaysTrue, L1, L2);
  Assert::IsTrue(equalList(L1, v2));
  Assert::IsTrue(equalList(L2, v3));
}

TEST_CASE("Problem11", ProjectNone) {
  Elem const * const L = buildList(v1);
  Elem *L1 = new Elem{ 0, nullptr }, *L2 = new Elem{ 1, nullptr };
  project(L, alwaysFalse, L1, L2);
  Assert::AreEqual(L1, nullptr);
  Assert::AreEqual(L2, nullptr);
}

TEST_CASE("Problem11", GreaterThanThreeProject) {
  Elem const * const L = buildList(v1);
  Elem *L1 = new Elem{ 0, nullptr }, *L2 = new Elem{ 1, nullptr };
  project(L, greaterThanThree, L1, L2);
  Assert::IsTrue(equalList(L1, v4));
  Assert::IsTrue(equalList(L2, v5));
}

TEST_CASE("Problem11", GreaterThanThreeProjectOddLength) {
  Elem const * const L = buildList(v2);
  Elem *L1 = new Elem{ 0, nullptr }, *L2 = new Elem{ 1, nullptr };
  project(L, greaterThanThree, L1, L2);
  Assert::IsTrue(equalList(L1, v6));
  Assert::IsTrue(equalList(L2, v7));
}
