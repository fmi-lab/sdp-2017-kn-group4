#include "doctest.h"
#include "queue.h"

TEST_CASE("Construct an empty queue") {
  Queue q;

  CHECK(q.empty());
  CHECK(q.size() == 0);
}

TEST_CASE("Queue not empty after enqueue operation") {
  Queue q;
  q.enqueue(1);

  CHECK(!q.empty());
  CHECK(q.size() == 1);
}

TEST_CASE("Queue's front is the first enqueued element") {
  Queue q;

  SUBCASE("Queue with one element") {
    q.enqueue(42);

    CHECK(q.front() == 42);
  }

  SUBCASE("Queue with more than one element") {
    q.enqueue(42);
    q.enqueue(56);
    q.enqueue(33);

    CHECK(q.front() == 42);
  }
}

TEST_CASE("Enqueue and dequeue operations") {
  Queue q;

  REQUIRE(q.empty());

  SUBCASE("One enqueue and one dequeue operation") {
    q.enqueue(42);

    CHECK(q.dequeue() == 42);
    CHECK(q.empty());
  }

  SUBCASE("Multiple enqueue and dequeue operations") {
    for (int i = 0; i < 10; ++i) {
      q.enqueue(i);
    }

    for (int i = 0; i < 10; ++i) {
      CHECK(q.dequeue() == i);
    }

    CHECK(q.empty());
  }
}
