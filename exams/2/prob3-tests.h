#include "UnitTestFramework.h"

#include <sstream>

using Matrix = int[100][100];

Cell* createMatrix(Matrix a, int m, int n) {
  Cell* result;
  Cell** p = &result;
  for(int i = 0; i < n; i++, p = &(*p)->right)
    *p = new Cell{ a[0][i], nullptr, nullptr };
  Cell* prow = result;
  p = &result->down;
  for(int i = 1; i < m; i++, p = &(*p)->down, prow = prow->down, p = &prow->down) {
    Cell* pp = prow;
    for(int j = 0; j < n; j++, pp = pp->right, p = &(*p)->right)
      *p = pp->down = new Cell { a[i][j], nullptr, nullptr };
  }
  return result;
}

std::string toStringRows(Cell* m) {
  std::ostringstream result;
  result << "{";
  for(; m; m = m->down) {
    result << "{";
    for(Cell* p = m; p; p = p->right)
      result << p->data << ' ';
    result << "}";
  }
  result << "}";
  return result.str();
}

std::string toStringCols(Cell* m) {
  std::ostringstream result;
  result << "{";
  for(; m; m = m->right) {
    result << "{";
    for(Cell* p = m; p; p = p->down)
      result << p->data << ' ';
    result << "}";
  }
  result << "}";
  return result.str();
}

Matrix M1 = { 10 };

Matrix M2 = {
  { 5, 4 },
  { 7, 3 }
};

Matrix M3 = {
  { 0, 0, 0 },
  { 2, 3, 0 },
  { 0, 1, 0 }
};

Matrix M4 = {
  { 1, 2, 3, 4 },
  { 5, 2, 7, 4 },
  { 8, 7, 3, 1 },
  { 3, 6, 5, 4 }
};

TEST_CASE("Problem3", Problem3_OneCell) {
  Cell* M = copySubmatrix(createMatrix(M1, 1, 1), 1);
  Assert::AreEqual(toStringRows(M), "{{10 }}");
  Assert::AreEqual(toStringCols(M), "{{10 }}");
}

TEST_CASE("Problem3", Problem3_OneCellMaximum) {
  Cell* M = copySubmatrix(createMatrix(M2, 2, 2), 1);
  Assert::AreEqual(toStringRows(M), "{{7 }}");
  Assert::AreEqual(toStringCols(M), "{{7 }}");
}

TEST_CASE("Problem3", Problem3_EntireMatrixMaximum) {
  Cell* M = copySubmatrix(createMatrix(M2, 2, 2), 2);
  Assert::AreEqual(toStringRows(M), "{{5 4 }{7 3 }}");
  Assert::AreEqual(toStringCols(M), "{{5 7 }{4 3 }}");
}

TEST_CASE("Problem3", Problem3_TwoByTwoMaximum) {
  Cell* M = copySubmatrix(createMatrix(M3, 3, 3), 2);
  Assert::AreEqual(toStringRows(M), "{{2 3 }{0 1 }}");
  Assert::AreEqual(toStringCols(M), "{{2 0 }{3 1 }}");
}

TEST_CASE("Problem3", Problem3_Example) {
  Cell* M = copySubmatrix(createMatrix(M4, 4, 4), 2);
  Assert::AreEqual(toStringRows(M), "{{8 7 }{3 6 }}");
  Assert::AreEqual(toStringCols(M), "{{8 3 }{7 6 }}");
}

TEST_CASE("Problem3", Problem3_ExampleThreeByThree) {
  Cell* M = copySubmatrix(createMatrix(M4, 4, 4), 3);
  Assert::AreEqual(toStringRows(M), "{{5 2 7 }{8 7 3 }{3 6 5 }}");
  Assert::AreEqual(toStringCols(M), "{{5 8 3 }{2 7 6 }{7 3 5 }}");
}
