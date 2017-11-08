#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <stack>

std::string repeat(std::string const& s, int count) {
  std::string result;

  for (int i = 0; i < count; ++i) {
    result += s;
  }

  return result;
}

std::string decode(std::string const& compressed) {
  std::stack<std::string> s;
  s.push("");

  for (size_t i = 0, length = compressed.length(); i < length; ++i) {
    char c = compressed[i];

    if (std::isdigit(c)) {
      std::string number;
      while (compressed[i] != '(') {
        number += compressed[i];
        ++i;
      }

      s.push(number);
      s.push("");
    } else if (c >= 'A' && c <= 'Z') {
      s.top() += c;
    } else if (c == ')') {
      std::string current = s.top();
      s.pop();

      int count = std::stoi(s.top());
      s.pop();

      s.top() += repeat(current, count);
    }
  }

  return s.top();
}

TEST_CASE("decode") {
  CHECK(decode("") == "");
  CHECK(decode("A") == "A");
  CHECK(decode("AB") == "AB");
  CHECK(decode("3(A)") == "AAA");
  CHECK(decode("3(AB2(B))") == "ABBBABBBABBB");
  CHECK(decode("12(ZQ)") == "ZQZQZQZQZQZQZQZQZQZQZQZQ");
  CHECK(decode("3(2(AB)C2(B))") == "ABABCBBABABCBBABABCBB");
  CHECK(decode("3(2(AB)C2(B))XY10(D)") == "ABABCBBABABCBBABABCBBXYDDDDDDDDDD");
}
