#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <queue>
#include <stack>

void reverse(std::queue<int>& q) {
  if (q.empty()) {
    return;
  }

  int front = q.front();
  q.pop();

  reverse(q);

  q.push(front);
}

void reverse_iter(std::queue<int>& q) {
  std::stack<int> s;

  while (!q.empty()) {
    s.push(q.front());
    q.pop();
  }

  while (!s.empty()) {
    q.push(s.top());
    s.pop();
  }
}

TEST_CASE("reverse") {
  std::queue<int> q;

  SUBCASE("the empty queue") {
    reverse(q);

    CHECK(q.empty());
  }

  SUBCASE("queue with one element") {
    q.push(1);
    reverse(q);

    CHECK(q.size() == 1);
    CHECK(q.front() == 1);
  }

  SUBCASE("queue with more than one element") {
    for (int n : {1, 23, 7, 42}) {
      q.push(n);
    }
    reverse(q);

    for (int n : {42, 7, 23, 1}) {
      CHECK(q.front() == n);
      q.pop();
    }
  }
}

TEST_CASE("reverse_iter") {
  std::queue<int> q;

  SUBCASE("the empty queue") {
    reverse_iter(q);

    CHECK(q.empty());
  }

  SUBCASE("queue with one element") {
    q.push(1);
    reverse_iter(q);

    CHECK(q.size() == 1);
    CHECK(q.front() == 1);
  }

  SUBCASE("queue with more than one element") {
    for (int n : {1, 23, 7, 42}) {
      q.push(n);
    }
    reverse_iter(q);

    for (int n : {42, 7, 23, 1}) {
      CHECK(q.front() == n);
      q.pop();
    }
  }
}
