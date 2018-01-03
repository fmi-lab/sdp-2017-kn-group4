#include <functional>
#include <iostream>
#include "suspension.cpp"

template <typename T>
class Stream;

template <typename T>
class Cell {
  T value;
  Stream<T> tail;

public:
  Cell() = default;

  Cell(T value, Stream<T> tail):
    value(std::move(value)), tail(std::move(tail)) {}

  explicit Cell(T value): value(value) {}

  T get_value() const {
    return value;
  }

  Stream<T> get_tail() const {
    return tail;
  }
};

template <typename T>
class Stream {
  std::shared_ptr<Suspension<Cell<T>>> lazy_cell;

public:
  Stream() = default;

  explicit Stream(std::function<Cell<T>()> f):
    lazy_cell(std::make_shared<Suspension<Cell<T>>>(f)) {}

  bool is_empty() const {
    return !lazy_cell;
  }

  T get() const {
    return lazy_cell->get().get_value();
  }

  Stream<T> tail() const {
    return lazy_cell->get().get_tail();
  }

  Stream take(int n) const {
    if (n == 0 || is_empty()) {
      return Stream();
    }

    auto cell = lazy_cell;

    return Stream([cell, n] {
      auto value = cell->get().get_value();
      auto tail = cell->get().get_tail();

      return Cell<T>(std::move(value), tail.take(n - 1));
    });
  }
};

Stream<int> ints_from(int n) {
  return Stream<int>([n] { return Cell<int>(n, ints_from(n + 1)); });
}

Stream<int> range(int n, int m) {
  return Stream<int>([n, m] { return Cell<int>(n, range(n + 1, m)); });
}

template <typename T, typename F>
void for_each(Stream<T> stream, F f) {
  while (!stream.is_empty()) {
    f(stream.get());
    stream = stream.tail();
  }
};

template <typename T, typename U, typename F>
auto zip_with(Stream<T> s1, Stream<U> s2, F f) -> Stream<decltype(f(s1.get(), s2.get()))> {
  using V = decltype(f(s1.get(), s2.get()));

  return Stream<V>([s1, s2, f] {
    return Cell<V>(f(s1.get(), s2.get()), zip_with(s1.tail(), s2.tail(), f));
  });
}

Stream<uint64_t> fibonacci() {
  return Stream<uint64_t>([] {
    return Cell<uint64_t>(0, Stream<uint64_t>([] {
      auto fibs = fibonacci();
      auto fibs_tail = fibs.tail();
      return Cell<uint64_t>(1, zip_with(std::move(fibs), std::move(fibs_tail),
                                   [](uint64_t x, uint64_t y) { return x + y; }));
    }));
  });
}

TEST_CASE("Stream") {
//  for_each(ints_from(0).take(100), [](int n) { std::cout << n << '\n'; });
  auto fibs = fibonacci().take(47);

  for_each(fibs, [](int n) { std::cout << n << '\n'; });
//  for_each(fibs, [](int n) { std::cout << n << '\n'; });
}
