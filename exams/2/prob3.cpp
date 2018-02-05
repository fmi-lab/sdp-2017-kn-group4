/////////////////////////////////////////////////////////////
//
// Author: попълнете името си тук
// FN: попълнете факултетния си номер тук
// Date: 21.01.2018
//

///
/// Структура, описваща клетка в матрица
///
struct Cell {
  int data;
  Cell* right;
  Cell* down;
};

// Да се реализира функция,
// [подходящ тип] copySubmatrix([подходящ тип] M, int n)
// която по дадена матрица M с поне n реда и поне n колони, зададена с указател към най-горна най-лява клетка, връща копие на такава нейна подматрица с размери n × n, в която сумата на елементите е най-голяма измежду всички такива подматрици.
int rowsCount(Cell const* M) {
  int count = 0;

  while (M) {
    ++count;
    M = M->down;
  }

  return count;
}

int columnsCount(Cell const* M) {
  int count = 0;

  while (M) {
    ++count;
    M = M->right;
  }

  return count;
}

int matrixSum(Cell const* M, int n) {
  int sum = 0;

  for (int i = 0; i < n; ++i) {
    Cell const* rowIter = M;
    for (int j = 0; j < n; ++j) {
      sum += rowIter->data;
      rowIter = rowIter->right;
    }
    M = M->down;
  }

  return sum;
}

Cell* matrixCopy(Cell const* M, int n) {
  Cell* copy = nullptr;
  Cell** copyIter = &copy;
  Cell** prevRow = nullptr;
  for (int i = 0; i < n; ++i) {
    Cell const* rowIter = M;
    Cell** copyRowIter = copyIter;
    for (int j = 0; j < n; ++j) {
      *copyRowIter = new Cell { rowIter->data, nullptr, nullptr };
      if (prevRow) {
        (*prevRow)->down = *copyRowIter;
        prevRow = &(*prevRow)->right;
      }
      rowIter = rowIter->right;
      copyRowIter = &(*copyRowIter)->right;
    }
    M = M->down;
    prevRow = copyIter;
    copyIter = &(*copyIter)->down;
  }

  return copy;
}

Cell* copySubmatrix(Cell const* M, int n) {
  int rowsBound = rowsCount(M) - n;
  int columnsBound = columnsCount(M) - n;

  int maxSum = matrixSum(M, n);
  Cell const* maxSubmatrix = M;
  for (int i = 0; i <= rowsBound; ++i) {
    Cell const* rowIter = M;
    for (int j = 0; j <= columnsBound; ++j) {
      int currentSum = matrixSum(rowIter, n);
      if (currentSum > maxSum) {
        maxSum = currentSum;
        maxSubmatrix = rowIter;
      }
      rowIter = rowIter->right;
    }
    M = M->down;
  }

  return matrixCopy(maxSubmatrix, n);
}

//-------------------------------------------------------------------------
//
// ВАЖНО: Преди предаване на решението, моля премахнете коментара от дадения по-долу ред,
//        за да активирате автоматичните тестове за решението си.
//
//-------------------------------------------------------------------------
#include "prob3-tests.h"

#include "UnitTestFramework.h"

int main() {

  //-------------------------------------------------------------------------
  //
  // ВАЖНО: При предаване на работата във тялото на функцията main не трябва да се
  //        изпълнява нищо друго освен функцията RunTests().
  //
  //-------------------------------------------------------------------------
  RunTests();

  return 0;
}
