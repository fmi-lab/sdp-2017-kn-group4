#include "doctest.h"
#include "calculator.h"

TEST_CASE("Construct with default initial state") {
  Calculator calculator;

  CHECK(calculator.get_state() == 0);
}

TEST_CASE("Construct with nondefault initial state") {
  Calculator calculator(1);

  CHECK(calculator.get_state() == 1);
}

TEST_CASE("The state can be changed by applying operations to it") {
  Calculator calculator;

  REQUIRE(calculator.get_state() == 0);

  auto add = [](double x, double y) { return x + y; };
  auto subtract = [](double x, double y) { return x - y; };
  auto multiply = [](double x, double y) { return x * y; };
  auto divide = [](double x, double y) { return x / y; };

  SUBCASE("Applying addition") {
    calculator.apply_operation(add, 1);
    CHECK(calculator.get_state() == 1);

    calculator.apply_operation(add, 3);
    CHECK(calculator.get_state() == 4);

    calculator.apply_operation(add, -2);
    CHECK(calculator.get_state() == 2);
  }

  SUBCASE("Applying different operations") {
    calculator.apply_operation(add, 3);
    CHECK(calculator.get_state() == 3);

    calculator.apply_operation(multiply, 4);
    CHECK(calculator.get_state() == 12);

    calculator.apply_operation(subtract, 1);
    CHECK(calculator.get_state() == 11);

    calculator.apply_operation(divide, 2);
    CHECK(calculator.get_state() == doctest::Approx(5.5));
  }
}

TEST_CASE("Undo operations") {
  Calculator calculator;

  REQUIRE(calculator.get_state() == 0);

  SUBCASE("Undo when no operations have been applied") {
    CHECK(calculator.undo(0) == 0);
    CHECK(calculator.get_state() == 0);
    CHECK(calculator.undo(1) == 0);
    CHECK(calculator.get_state() == 0);
    CHECK(calculator.undo(2) == 0);
    CHECK(calculator.get_state() == 0);
  }

  auto add = [](double x, double y) { return x + y; };

  SUBCASE("Undo when one operation has been applied") {
    calculator.apply_operation(add, 1);

    CHECK(calculator.undo(0) == 1);
    CHECK(calculator.get_state() == 1);
    CHECK(calculator.undo(1) == 0);
    CHECK(calculator.get_state() == 0);
    CHECK(calculator.undo(1) == 0);
    CHECK(calculator.get_state() == 0);
  }

  SUBCASE("Undo when more than one operations have been applied") {
    calculator.apply_operation(add, 1);
    calculator.apply_operation(add, 2);
    calculator.apply_operation(add, 3);

    SUBCASE("Undo zero operations") {
      CHECK(calculator.undo(0) == 6);
      CHECK(calculator.get_state() == 6);
    }

    SUBCASE("Undo one operation at a time") {
      CHECK(calculator.undo(1) == 3);
      CHECK(calculator.get_state() == 3);
      CHECK(calculator.undo(1) == 1);
      CHECK(calculator.get_state() == 1);
      CHECK(calculator.undo(1) == 0);
      CHECK(calculator.get_state() == 0);
      CHECK(calculator.undo(1) == 0);
      CHECK(calculator.get_state() == 0);
    }

    SUBCASE("Undo two operations at a time") {
      CHECK(calculator.undo(2) == 1);
      CHECK(calculator.get_state() == 1);
      CHECK(calculator.undo(2) == 0);
      CHECK(calculator.get_state() == 0);
    }

    SUBCASE("Undo three operations at a time") {
      CHECK(calculator.undo(3) == 0);
      CHECK(calculator.get_state() == 0);
      CHECK(calculator.undo(3) == 0);
      CHECK(calculator.get_state() == 0);
    }

    SUBCASE("Undo mixed number of operations") {
      CHECK(calculator.undo(1) == 3);
      CHECK(calculator.get_state() == 3);
      CHECK(calculator.undo(2) == 0);
      CHECK(calculator.get_state() == 0);
      CHECK(calculator.undo(1) == 0);
      CHECK(calculator.get_state() == 0);
    }
  }
}

TEST_CASE("Redo operations") {
  Calculator calculator;

  REQUIRE(calculator.get_state() == 0);

  SUBCASE("Redo when no operations have been undone") {
    CHECK(calculator.redo(0) == 0);
    CHECK(calculator.get_state() == 0);
    CHECK(calculator.redo(1) == 0);
    CHECK(calculator.get_state() == 0);
    CHECK(calculator.redo(2) == 0);
    CHECK(calculator.get_state() == 0);
  }

  auto add = [](double x, double y) { return x + y; };

  SUBCASE("Redo when one operation has been undone") {
    calculator.apply_operation(add, 1);
    calculator.apply_operation(add, 2);
    calculator.apply_operation(add, 3);

    calculator.undo(1);

    CHECK(calculator.redo(1) == 6);
    CHECK(calculator.get_state() == 6);
    CHECK(calculator.redo(1) == 6);
    CHECK(calculator.get_state() == 6);
  }

  SUBCASE("Redo when more than one operations have been undone") {
    calculator.apply_operation(add, 1);
    calculator.apply_operation(add, 2);
    calculator.apply_operation(add, 3);

    calculator.undo(3);

    SUBCASE("Redo zero operations") {
      CHECK(calculator.redo(0) == 0);
      CHECK(calculator.get_state() == 0);
    }

    SUBCASE("Redo one operation at a time") {
      CHECK(calculator.redo(1) == 1);
      CHECK(calculator.get_state() == 1);
      CHECK(calculator.redo(1) == 3);
      CHECK(calculator.get_state() == 3);
      CHECK(calculator.redo(1) == 6);
      CHECK(calculator.get_state() == 6);
      CHECK(calculator.redo(1) == 6);
      CHECK(calculator.get_state() == 6);
    }

    SUBCASE("Redo two operations at a time") {
      CHECK(calculator.redo(2) == 3);
      CHECK(calculator.get_state() == 3);
      CHECK(calculator.redo(2) == 6);
      CHECK(calculator.get_state() == 6);
    }

    SUBCASE("Redo three operations at a time") {
      CHECK(calculator.redo(3) == 6);
      CHECK(calculator.get_state() == 6);
      CHECK(calculator.redo(3) == 6);
      CHECK(calculator.get_state() == 6);
    }

    SUBCASE("Redo mixed number of operations") {
      CHECK(calculator.redo(1) == 1);
      CHECK(calculator.get_state() == 1);
      CHECK(calculator.redo(2) == 6);
      CHECK(calculator.get_state() == 6);
      CHECK(calculator.redo(1) == 6);
      CHECK(calculator.get_state() == 6);
    }

    SUBCASE("Redo after applying operation preserves the current state") {
      calculator.apply_operation(add, 6);
      CHECK(calculator.redo(1) == 6);
      CHECK(calculator.get_state() == 6);
    }
  }
}

TEST_CASE("Mix undo and redo operations") {
  Calculator calculator;

  auto add = [](double x, double y) { return x + y; };

  for (int i = 0; i < 10; ++i) {
    calculator.apply_operation(add, 1);
  }

  CHECK(calculator.undo(3) == 7);
  CHECK(calculator.get_state() == 7);
  CHECK(calculator.redo(2) == 9);
  CHECK(calculator.get_state() == 9);
  CHECK(calculator.undo(5) == 4);
  CHECK(calculator.get_state() == 4);
}
