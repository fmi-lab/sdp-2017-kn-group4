#include <iostream>
#include <vector>
#include <unordered_map>

template <typename T, typename U>
using Groups = std::unordered_map<U, std::vector<T>>;

// O(n)
template <typename T, typename U>
Groups<U, T> group_by(std::vector<T> const& v, U (*f)(T)) {
  Groups<U, T> groups;

  for (auto const& x : v) {
    groups[f(x)].push_back(x);
  }

  return groups;
}

using Pairs = std::vector<std::pair<int, int>>;

// O(n)
Pairs pairs_sum_to_k(std::vector<int> const& v, int k) {
  Pairs pairs;

  std::unordered_map<int, bool> present;

  for (auto const& x : v) {
    if (present[k - x]) {
      pairs.emplace_back(std::make_pair(x, k - x));
    }
    present[x] = true;
  }

  return pairs;
}

// n - number of sets
// m - average number of elements in each set
//
std::vector<int> n_intersection(std::vector<std::vector<int>> const& sets) {
  std::vector<int> result;

  int smallest_set_index = 0;
  size_t smallest_set_size = sets[0].size();

  // O(m * log(m))
  std::sort(sets[0].begin(), sets[0].end());

  // O(n * m * log(m))
  for (int i = 1; i < sets.size(); ++i) {
    std::sort(sets[i].begin(), sets[i].end());

    if (sets[i].size() < smallest_set_size) {
      smallest_set_index = i;
      smallest_set_size = sets[i].size();
    }
  }

  std::unordered_map<int, u_long> elements;
  // O(m)
  for (auto const& x : sets[smallest_set_index]) {
    ++elements[x];
  }

  // O (m * n * log(m) + m^2)
  for (auto const& p : elements) {
    int element = p.first;
    u_long frequency = p.second;

    // O(n * log(m))
    for (int i = 0; i < sets.size(); ++i) {
      if (i != smallest_set_index) {
        // O(log(m))
        if (std::binary_search(sets[i].begin(), sets[i].end(), element)) {
          // O(log(m))
          u_long left_index =
            std::lower_bound(sets[i].begin(), sets[i].end(), element) - sets[i].begin();

          // O(log(m))
          u_long right_index =
            std::upper_bound(sets[i].begin(), sets[i].end(), element) - sets[i].begin();

          if (right_index - left_index < frequency) {
            frequency = right_index - left_index;
          }
        } else {
          frequency = 0;
          break;
        }
      }
    }

    if (frequency > 0) {
      // O(m)
      for (u_long i = 0; i < frequency; ++i) {
        result.push_back(element);
      }
    }
  }

  return result;
}

int mod3(int n) {
  return n % 3;
}

int main() {
  std::vector<int> v = {1, 2, 3, 4, 5};

  Groups<int, int> groups = group_by(v, mod3);

  for (auto const& group : groups) {
    std::cout << group.first << ": ";
    for (auto const& x : group.second) {
      std::cout << x << ' ';
    }
    std::cout << '\n';
  }

  Pairs pairs = pairs_sum_to_k(v, 7);

  for (auto const& pair : pairs) {
    std::cout << '(' << pair.first << ", " << pair.second << ") ";
  }
  std::cout << '\n';

  return 0;
}