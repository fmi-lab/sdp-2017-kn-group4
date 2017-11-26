#include <forward_list>
#include "doctest.h"

template <typename T, typename F>
std::forward_list<T> filter(std::forward_list<T> const& l, F f) {
  std::forward_list<T> result;

  for (auto const& x : l) {
    if (f(x)) {
      result.push_front(x);
    }
  }

  result.reverse();

  return result;
};

TEST_CASE("filter") {
  auto even = [](int x) { return x % 2 == 0; };
  auto odd = [&even](int x) { return !even(x); };

  SUBCASE("the empty list") {
    std::forward_list<int> empty;

    CHECK_EQ(filter(empty, even), std::forward_list<int>());
    CHECK_EQ(filter(empty, odd), std::forward_list<int>());
  }

  SUBCASE("list with one element") {
    std::forward_list<int> l = {1};
    std::forward_list<int> evens;
    std::forward_list<int> odds = {1};

    CHECK_EQ(filter(l, even), evens);
    CHECK_EQ(filter(l, odd), odds);
  }

  SUBCASE("list with more than one element") {
    std::forward_list<int> l = {1, 2, 3, 4, 5};
    std::forward_list<int> evens = {2, 4};
    std::forward_list<int> odds = {1, 3, 5};

    CHECK_EQ(filter(l, even), evens);
    CHECK_EQ(filter(l, odd), odds);
  }
}
