/////////////////////////////////////////////////////////////
//
// Author: попълнете името си тук
// FN: попълнете факултетния си номер тук
// Date: 6.01.2018
//

#include <vector>

///
/// Структура, описваща възел в двоично дърво
///
struct Node {
  int x;
  Node* left;
  Node* right;
};

/*
Да се дефинира клас LevelIterator, с чиято помощ могат да се получат последователно броят на елементите на поредните нива в дадено дърво. Класът да предоставя следните методи:
*/

class LevelIterator {
  std::vector<Node const*> current_level;

  // Класът да предоставя следните методи:
public:

  // Конструктор, който създава итератор чрез указател към корена на дадено дърво
  LevelIterator(Node const* root) {
    if (root) {
      current_level = { root };
    }
  }

  // Метод int currentSum() const, който връща сумата от елементите на текущото ниво
  int currentSum() const {
    int sum = 0;

    for (auto const& node : current_level) {
      sum += node->x;
    }

    return sum;
  }

  // Метод void next(), чрез който итераторът преминава към следващото ниво
  void next() {
    std::vector<Node const*> next_level;

    for (auto const& node : current_level) {
      if (node->left) {
        next_level.push_back(node->left);
      }
      if (node->right) {
        next_level.push_back(node->right);
      }
    }

    current_level = std::move(next_level);
  }

  // Метод bool end() const, който проверява дали итераторът е преминал
  // след последното ниво в дървото.
  bool end() const {
    return current_level.empty();
  }

};

//-------------------------------------------------------------------------
//
// ВАЖНО: Преди предаване на решението, моля премахнете коментара от дадения по-долу ред,
//        за да активирате автоматичните тестове за решението си.
//
//-------------------------------------------------------------------------
#include "prob12-tests.h"

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
