/////////////////////////////////////////////////////////////
//
// Author: попълнете името си тук
// FN: попълнете факултетния си номер тук
// Date: 21.01.2018
//

#include <string>
#include <map>
#include <set>

// Да се реализира функция
// std::string mostCommon (char G[100][100], int N, int k);
// която намира най-често срещаната (или една измежду най-често срещаните) k-буквени думи, които могат да се прочетат между всички различни двойки върхове в G.
void countWordsFrom(char G[100][100], int N, int start, int end, int k,
                    std::string& word, std::set<std::string>& counted,
                    std::map<std::string, int>& wordCount) {
  if (k == 0) {
    if (start == end && counted.find(word) == counted.end()) {
      counted.insert(word);
      ++wordCount[word];
    }

    return;
  }

  for (int i = 0; i < N; ++i) {
    if (G[start][i]) {
      word.push_back(G[start][i]);
      countWordsFrom(G, N, i, end, k - 1, word, counted, wordCount);
      word.pop_back();
    }
  }
}

std::string mostCommon(char G[100][100], int N, int k) {
  std::map<std::string, int> wordCount;

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      std::string word;
      std::set<std::string> counted;
      countWordsFrom(G, N, i, j, k, word, counted, wordCount);
    }
  }

  int maxCount = 0;
  std::string mostCommonWord;
  for (auto const& kvp : wordCount) {
    if (kvp.second > maxCount) {
      maxCount = kvp.second;
      mostCommonWord = kvp.first;
    }
  }

  return mostCommonWord;
}

//-------------------------------------------------------------------------
//
// ВАЖНО: Преди предаване на решението, моля премахнете коментара от дадения по-долу ред,
//        за да активирате автоматичните тестове за решението си.
//
//-------------------------------------------------------------------------
#include "prob2-tests.h"

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
