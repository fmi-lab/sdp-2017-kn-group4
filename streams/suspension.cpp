#include <functional>
#include "doctest.h"

template <typename T>
class Suspension {
  std::function<T()> f;
  T const& (*thunk)(Suspension*);
  T memo;

  static T const& thunk_force(Suspension* suspension) {
    return suspension->set_memo();
  }

  static T const& thunk_get(Suspension* suspension) {
    return suspension->get_memo();
  }

  T const& get_memo() {
    return memo;
  }

  T const& set_memo() {
    memo = f();
    thunk = &thunk_get;

    return get_memo();
  }

public:
  explicit Suspension(std::function<T()> f): f(f), thunk(&thunk_force) {}

  T const& get() {
    return thunk(this);
  }
};

TEST_CASE("Suspension") {
  auto one = [] { return 1; };
  CHECK_EQ(Suspension<int>(one).get(), 1);

  int x = 40;
  int y = 2;
  CHECK_EQ(Suspension<int>([x, y] { return x + y; }).get(), 42);
}
