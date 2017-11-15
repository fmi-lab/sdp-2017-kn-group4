#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <queue>

template <typename T>
bool all_different(std::queue<T> q) {
  size_t q_size = q.size();

  for (size_t i = 0; i < q_size; ++i) {
    T current = q.front();
    q.pop();

    for (size_t j = i + 1; j < q_size; ++j) {
      if (q.front() == current) {
        return false;
      }

      q.push(q.front());
      q.pop();
    }
  }

  return true;
}

TEST_CASE("all_different") {
  std::queue<int> q;

  SUBCASE("in empty queue") {
    CHECK(all_different(q));
  }

  SUBCASE("in queue with one element") {
    q.push(1);

    CHECK(all_different(q));
  }

  SUBCASE("in queue with different elements") {
    q.push(1);
    q.push(2);
    q.push(3);

    CHECK(all_different(q));
  }

  SUBCASE("in queue with two identical elements") {
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(1);

    CHECK_FALSE(all_different(q));
  }

  SUBCASE("in queue with more than two identical elements") {
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(3);
    q.push(2);

    CHECK_FALSE(all_different(q));
  }

  SUBCASE("in queue with all identical elements") {
    q.push(1);
    q.push(1);
    q.push(1);
    q.push(1);

    CHECK_FALSE(all_different(q));
  }
}