#include <forward_list>
#include <string>
#include <functional>
#include "doctest.h"

// Първи вариант:
// T е типът на елементите на списъка l, U е типът на елементите
// на списъка, който връща map. Тогава типът на f трябва да бъде функция, която
// приема аргумент от тип T и връща резултат от тип U (f преобразува обект от
// тип T до обект от тип U). Това можем да изразим чрез типа
// std::function<U(T)>.
// Когато извикваме map, задължително трябва да указваме типовете T и U:
// std::forward_list<int> l1 = {1, 2, 3, 4, 5};
// std::forward_list<int> l2 = map<int, int>(l1, [](int x) { return x + 1; });
// Компилаторът не може да изведе типа U.
template <typename T, typename U>
std::forward_list<U> map(std::forward_list<T> const& l, std::function<U(T)> f) {
  std::forward_list<U> result;

  for (auto const& x : l) {
    result.push_front(f(x));
  }

  result.reverse();

  return result;
}

// Втори вариант:
// T е типът на елементите на списъка l, F е тип на трансформиращата фунцкия f.
// map трябва да връща списък (std::forward_list) от елементи, чийто тип е типът
// на връщане на функцията f. За да изразим този тип, можем да използваме
// следния синтаксис въведен в C++11:
// "auto function -> return type", където "return type" можем да определим
// чрез "decltype(expression)" (въвдено в C++11). decltype приема израз и връща
// типа на израза. В нашия случай имаме decltype(f(T())):
// конструираме обект от тип T - "T()", подаваме го на f - "f(T())" и определяме
// типа на израза f(T()) - "decltype(f(T()))". По този начин намираме типа на
// връщане на f. Тогава типът на връщане на map трябва да бъде
// std::forward_list<decltype(f(T()))>
// При този вариант на типизиране на параметрите на map няма нужда да указваме
// типовете T и F:
// std::forward_list<int> l = {1, 2, 3, 4, 5};
// std::forward_list<int> plus_one = map(l, [](int x) { return x + 1; });
// Компилаторът извежда типовете T и F, а чрез decltype извежда и типът на
// връщане.
/*
template <typename T, typename F>
auto map(std::forward_list<T> const& l, F f) -> std::forward_list<decltype(f(T()))> {
  std::forward_list<decltype(f(T()))> result;

  for (auto const& x : l) {
    result.push_front(f(x));
  }

  result.reverse();

  return result;
}
*/

// Трети вариант:
// Като втори вариант, но не указваме типа на връщане на map експлицитно.
// Компилаторът ще го изведе от типа на резултата, който връща map.
// Използваме синтаксиса "auto function" въведен в C++14. Забележете,
// че все още ни се налага да използваме decltype, за да определим типа на
// резултата, който връщаме.
template <typename T, typename F>
auto map(std::forward_list<T> const& l, F f) {
  std::forward_list<decltype(f(T()))> result;

  for (auto const& x : l) {
    result.push_front(f(x));
  }

  result.reverse();

  return result;
}

TEST_CASE("map") {
  auto add_one = [](int x) { return x + 1; };
  auto square = [](int x) { return x * x; };

  SUBCASE("the empty list") {
    std::forward_list<int> empty;

    CHECK_EQ(map(empty, add_one), std::forward_list<int>());
    CHECK_EQ(map(empty, square), std::forward_list<int>());
  }

  SUBCASE("list with one element") {
    std::forward_list<int> l = {1};
    std::forward_list<int> plus_one = {2};
    std::forward_list<int> squared = {1};

    CHECK_EQ(map(l, add_one), plus_one);
    CHECK_EQ(map(l, square), squared);
  }

  SUBCASE("list with more than one element") {
    std::forward_list<int> l = {1, 2, 3, 4, 5};
    std::forward_list<int> plus_one = {2, 3, 4, 5, 6};
    std::forward_list<int> squared = {1, 4, 9, 16, 25};

    CHECK_EQ(map(l, add_one), plus_one);
    CHECK_EQ(map(l, square), squared);
  }

  SUBCASE("list of strings to list of integers") {
    std::forward_list<std::string> l = {"1", "2", "3", "42"};
    std::forward_list<int> integers = {1, 2, 3, 42};
    auto to_integer = [](std::string const& s) { return std::stoi(s); };

    CHECK_EQ(map(l, to_integer), integers);
  }

  SUBCASE("list of strings to list of lists of integers") {
    std::forward_list<std::string> l = {"1", "2", "3", "42"};
    std::forward_list<std::forward_list<int>> integers = {{1}, {2}, {3}, {42}};
    auto to_list_of_integer = [](std::string const& s) {
      return std::forward_list<int>(1, std::stoi(s));
    };

    CHECK_EQ(map(l, to_list_of_integer), integers);
  }
}
