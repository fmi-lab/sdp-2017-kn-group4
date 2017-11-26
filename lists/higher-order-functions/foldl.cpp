#include <forward_list>
#include "doctest.h"

template <typename T, typename U, typename F>
U foldl(std::forward_list<T> const& l, U null_value, F f) {
  U result = null_value;

  for (auto const& x : l) {
    result = f(result, x);
  }

  return result;
};

TEST_CASE("foldl") {
  auto add = [](int x, int y) { return x + y; };
  auto multiply = [](int x, int y) { return x * y; };

  SUBCASE("the empty list") {
    std::forward_list<int> empty;

    CHECK_EQ(foldl(empty, 0, add), 0);
    CHECK_EQ(foldl(empty, 1, multiply), 1);
  }

  SUBCASE("list with one element") {
    std::forward_list<int> l = {42};

    CHECK_EQ(foldl(l, 0, add), 42);
    CHECK_EQ(foldl(l, 1, multiply), 42);
  }

  SUBCASE("list with more than one element") {
    std::forward_list<int> l = {1, 2, 3, 4, 5};

    CHECK_EQ(foldl(l, 0, add), 15);
    CHECK_EQ(foldl(l, 1, multiply), 120);
  }

  SUBCASE("list of integers to list of consecutive pairs") {
    std::forward_list<int> l = {1, 2, 3, 4, 5};
    std::forward_list<std::pair<int, int>> consecutive_pairs = {
      {1, 2}, {2, 3}, {3, 4}, {4, 5},
    };

    auto make_consecutive_pairs = [](std::forward_list<int> const& l) {
      std::forward_list<std::pair<int, int>> result;

      if (l.empty() || ++l.cbegin() == l.cend()) {
        return result;
      }

      result.push_front(std::make_pair(0, 0));
      result = foldl(l, result, [](auto&& acc, int x) {
        acc.push_front(std::make_pair(acc.front().second, x));
        return acc;
      });
      result.reverse();
      result.pop_front();
      result.pop_front();

      return result;
    };

    CHECK_EQ(make_consecutive_pairs(l), consecutive_pairs);
  }
}
