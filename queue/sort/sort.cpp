#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <queue>
#include <unordered_set>

int dequeue_min(std::queue<int>& q) {
  size_t q_size = q.size();

  int min = q.front();
  q.pop();

  for (size_t i = 1; i < q_size; ++i) {
    if (q.front() < min) {
      q.push(min);
      min = q.front();
    } else {
      q.push(q.front());
    }

    q.pop();
  }

  return min;
}

std::queue<int> sort(std::queue<int> q) {
  std::queue<int> sorted;

  while (!q.empty()) {
    sorted.push(dequeue_min(q));
  }

  return sorted;
}

TEST_CASE("dequeue_min") {
  std::queue<int> q;

  SUBCASE("from queue with one element") {
    q.push(42);

    CHECK(dequeue_min(q) == 42);
    CHECK(q.empty());
  }

  SUBCASE("from queue with more than one element") {
    for (int n : {42, 4, 11, 1, 50, 2}) {
      q.push(n);
    }

    CHECK(dequeue_min(q) == 1);

    std::unordered_set<int> s = {42, 4, 11, 50, 2};
    while (!q.empty()) {
      auto found = s.find(q.front());
      CHECK(found != s.end());
      s.erase(found);

      q.pop();
    }
  }

  SUBCASE("from queue with two identical elements") {
    for (int n : {42, 1, 4, 11, 1, 50, 2}) {
      q.push(n);
    }

    CHECK(dequeue_min(q) == 1);

    std::unordered_set<int> s = {42, 4, 11, 1, 50, 2};
    while (!q.empty()) {
      auto found = s.find(q.front());
      CHECK(found != s.end());
      s.erase(found);

      q.pop();
    }
  }
}

TEST_CASE("sort") {
  std::queue<int> q;

  SUBCASE("the empty queue") {
    CHECK(sort(q).empty());
  }

  SUBCASE("queue with one element") {
    q.push(42);
    std::queue<int> sorted = sort(q);
    CHECK(sorted.size() == 1);
    CHECK(sorted.front() == 42);
  }

  SUBCASE("queue with more than one element") {
    for (int n : {42, 4, 11, 1, 50, 2}) {
      q.push(n);
    }

    std::queue<int> sorted = sort(q);

    for (int n : {1, 2, 4, 11, 42, 50}) {
      CHECK(sorted.front() == n);
      sorted.pop();
    }
  }
}
