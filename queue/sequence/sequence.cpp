#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <queue>

int sequence(int n, int p) {
  int current = n;

  std::queue<int> q;

  for (int i = 0; i < p - 1; ++i) {
    q.push(current + 1);
    q.push(current * 2);

    current = q.front();
    q.pop();
  }

  return current;
}

TEST_CASE("sequence") {
  CHECK(sequence(42, 1) == 42);
  CHECK(sequence(42, 2) == 43);
  CHECK(sequence(42, 3) == 84);
  CHECK(sequence(42, 4) == 44);
  CHECK(sequence(42, 5) == 86);
  CHECK(sequence(42, 6) == 85);
  CHECK(sequence(42, 7) == 168);
}
