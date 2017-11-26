#include <forward_list>
#include "doctest.h"

template <typename T, typename U>
std::forward_list<std::pair<T, U>> zip(std::forward_list<T> const& l1,
                                       std::forward_list<U> const& l2) {
  std::forward_list<std::pair<T, U>> result;

  auto it1 = l1.cbegin();
  auto it2 = l2.cbegin();
  while (it1 != l1.cend() && it2 != l2.cend()) {
    result.push_front(std::make_pair(*it1++, *it2++));
  }

  result.reverse();

  return result;
};

TEST_CASE("zip") {
  SUBCASE("empty lists") {
    std::forward_list<int> empty;
    std::forward_list<std::pair<int, int>> result;

    CHECK_EQ(zip(empty, empty), result);
  }

  SUBCASE("empty and nonempty lists") {
    std::forward_list<int> empty;
    std::forward_list<int> nonempty = {1, 2, 3};
    std::forward_list<std::pair<int, int>> result;

    CHECK_EQ(zip(empty, nonempty), result);
    CHECK_EQ(zip(nonempty, empty), result);
  }

  SUBCASE("two nonempty lists with equal sizes") {
    std::forward_list<int> l1 = {1, 2, 3};
    std::forward_list<int> l2 = {4, 5, 6};
    std::forward_list<std::pair<int, int>> result = {{1, 4}, {2, 5}, {3, 6}};

    CHECK_EQ(zip(l1, l2), result);
  }

  SUBCASE("two nonempty lists with different sizes") {
    std::forward_list<int> l1 = {1, 2, 3, 4, 5};
    std::forward_list<int> l2 = {6, 7, 8};

    SUBCASE("where the first is bigger than the second") {
      std::forward_list<std::pair<int, int>> result = {{1, 6}, {2, 7}, {3, 8}};

      CHECK_EQ(zip(l1, l2), result);
    }

    SUBCASE("where the second is bigger than the first") {
      std::forward_list<std::pair<int, int>> result = {{6, 1}, {7, 2}, {8, 3}};

      CHECK_EQ(zip(l2, l1), result);
    }
  }
}
