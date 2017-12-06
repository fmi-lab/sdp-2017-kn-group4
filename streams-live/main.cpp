#include <iostream>

template <typename T>
class Suspension {
  std::function<T()> f;
  bool is_calculated;
  T memo;

public:

  Suspension(std::function<T()> f): f(f), is_calculated(false), memo(T()) {};

  T get() {
    if (is_calculated) {
      return memo;
    }

    is_calculated = true;
    memo = f();

    return memo;
  }
};

template <typename T>
class Stream;

template <typename T>
class Cell {
  T head;
  Stream<T> tail;

public:

  Cell() {}

  Cell(T head, Stream<T> tail): head(head), tail(tail) {};

  T get_head() const {
    return head;
  }

  Stream<T> get_tail() const {
    return tail;
  }
};

template <typename T>
class Stream {
  std::shared_ptr<Suspension<Cell<T>>> lazy_cell;

public:

  Stream() {}

  Stream(std::function<Cell<T>()> f)
    : lazy_cell(std::make_shared<Suspension<Cell<T>>>(f)) {}

  bool is_empty() {
    return !lazy_cell;
  }

  T get() const {
    return lazy_cell->get().get_head();
  }

  Stream tail() const {
    return lazy_cell->get().get_tail();
  }

  Stream take(int n) {
    if (n == 0) {
      return Stream();
    }

    auto cell = lazy_cell;

    return Stream([cell, n] {
      auto head = cell->get().get_head();
      auto tail = cell->get().get_tail();

      return Cell<T>(head, tail.take(n - 1));
    });
  }
};

template <typename T, typename U, typename F>
auto zip_with(Stream<T> s1, Stream<U> s2, F f) -> Stream<decltype(f(s1.get(), s2.get()))> {
  using V = decltype(f(s1.get(), s2.get()));

  return Stream<V>([s1, s2, f] {
    return Cell<V>(f(s1.get(), s2.get()), zip_with(s1.tail(), s2.tail(), f));
  });
}

Stream<int> fibonacci() {
  return Stream<int>([] {
    return Cell<int>(0, Stream<int>([] {
      auto fibs = fibonacci();
      auto fibs_tail = fibs.tail();

      return Cell<int>(1, zip_with(fibs, fibs_tail,
                                  [](int x, int y) { return x + y; }));
    }));
  });
}

template <typename T, typename F>
void for_each(Stream<T> stream, F f) {
  while (!stream.is_empty()) {
    f(stream.get());
    stream = stream.tail();
  }
}

Stream<int> integers_from(int n) {
  return Stream<int>([n] {
    return Cell<int>(n, integers_from(n + 1));
  });
}

int main() {
//  Stream<int> ints = integers_from(0).take(10);
//  for_each(ints, [](int x) { std::cout << x << '\n'; });
//  for_each(ints, [](int x) { std::cout << x << '\n'; });

  Stream<int> fibs = fibonacci().take(47);
  for_each(fibs, [](int x) { std::cout << x << '\n'; });

  return 0;
}