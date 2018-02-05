#include "UnitTestFramework.h"

#define GSIZE 100

using GraphMatrix = char[100][100];

GraphMatrix G0 = { 0 };

GraphMatrix G1 = {
  { 0 , 'a' }, 
  { 0 ,  0  }
};

GraphMatrix G2 = {
  {  0  , 'a' },
  { 'a' ,  0 }
};

GraphMatrix G3 = {
  { 0   , 'a' , 'b' },
  { 'a' ,  0  , 'b' }, 
  { 'b' , 'b' ,  0  }
};

GraphMatrix G4 = {
  { 0 , 'b' ,  0 ,  0,   'c' },
  { 0 ,  0  ,  0 , 'a' ,  0  },
  { 0 ,  0  ,  0 , 'c' ,  0  },
  { 0 , 'b' ,  0 ,  0  ,  0  },
  { 0 ,  0  ,  0 , 'd' ,  0  }
};


TEST_CASE("Problem2", Problem2_EmptyGraph) {
  Assert::AreEqual(mostCommon(G0, 1, 5), std::string(""));
}

TEST_CASE("Problem2", Problem2_SingleEdgeOneWord) {
  Assert::AreEqual(mostCommon(G1, 2, 1), std::string("a"));
}

TEST_CASE("Problem2", Problem2_SingleEdgeNoLongWords) {
  Assert::AreEqual(mostCommon(G1, 2, 5), std::string(""));
}

TEST_CASE("Problem2", Problem2_SimpleCycleOneWord) {
  Assert::AreEqual(mostCommon(G2, 2, 5), std::string("aaaaa"));
}

TEST_CASE("Problem2", Problem2_FullGraphManyWordsOneMostCommon) {
  Assert::AreEqual(mostCommon(G3, 3, 6), std::string("bbbbbb"));
}

TEST_CASE("Problem2", Problem2_Example) {
  Assert::AreEqual(mostCommon(G4, 5, 3), std::string("bab"));
}
