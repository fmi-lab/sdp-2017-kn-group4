/////////////////////////////////////////////////////////////
//
// Author: попълнете името си тук
// FN: попълнете факултетния си номер тук
// Date: 6.01.2018
//

///
/// Структура, описваща възел в линеен едносвързан списък
///
struct Elem {
  int x;
  Elem* next;
};

void erase(Elem* l) {
  if (!l) {
    return;
  }

  erase(l->next);
  delete l;
}

void push(Elem*& l, int x) {
  l = new Elem { x, l };
}

void reverse(Elem*& l) {
  Elem* prev = nullptr;

  while (l) {
    Elem* next = l->next;
    l->next = prev;
    prev = l;
    l = next;
  }

  l = prev;
}

void project(Elem const* l, bool (*p)(int), Elem*& l1, Elem*& l2) {
  erase(l1);
  erase(l2);
  l1 = nullptr;
  l2 = nullptr;

  int i = 0;
  while (l) {
    if (p(l->x)) {
      if (i % 2 == 0) {
        push(l1, l->x);
      } else {
        push(l2, l->x);
      }
    }

    ++i;
    l = l->next;
  }

  reverse(l1);
  reverse(l2);
}

/*
Да се реализира функция:
void project ([подходящ тип] L, [подходящ тип] p, [подходящ тип] L1, [подходящ тип] L2), където
L е указател към първия елемент на линеен едносвързан списък от четен брой числа, а p е едноместен предикат над числа (p: int ⟶ bool). Функцията project да създава и връща чрез L1 списък с всички елементи на четни позиции (започвайки от 0), за които p е истина, а чрез L2 списък с всички елементи на нечетни позиции (започвайки от 0) на елементи от L, за които p е истина.
*/

//-------------------------------------------------------------------------
//
// ВАЖНО: Преди предаване на решението, моля премахнете коментара от дадения по-долу ред,
//        за да активирате автоматичните тестове за решението си.
//
//-------------------------------------------------------------------------
#include "prob11-tests.h"

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