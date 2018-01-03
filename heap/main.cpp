#include <iostream>
#include <queue>

// Намира k-тия най-малък елемент в масив.
// Сложност: O(n + k * log(n))
int kth_smallest(int array[], int n, int k) {
  std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap(
    array, array + n, std::greater<int>()
  );

  for (int i = 0; i < k - 1; ++i) {
    min_heap.pop();
  }

  return min_heap.top();
}

// Намира k-тия най-малък елемент в масив, използвайки max heap.
// Сложност: O(k + (n - k) * log(k))
int kth_smallest_with_max_heap(int array[], int n, int k) {
  std::priority_queue<int> max_heap(array, array + k);

  for (int i = k; i < n; ++i) {
    if (array[i] < max_heap.top()) {
      max_heap.pop();
      max_heap.push(array[i]);
    }
  }

  return max_heap.top();
}

// Реализира структура Median, която съхранява редица от елементи и
// може да намира медианата на редицата. Поддържа следните 2 операции:
// void insert(x) - вмъква елемент в редицата със сложност O(log(n))
// double median() - намира медианата на редицата със сложност O(1)
class Median {
  std::priority_queue<int> max_heap;
  std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;
  int size;

public:

  Median(): size(0) {}

  void insert(int x) {
    if (size % 2 == 0) {
      max_heap.push(x);

      if (!min_heap.empty() && max_heap.top() > min_heap.top()) {
        max_heap.push(min_heap.top());
        min_heap.push(max_heap.top());
        min_heap.pop();
        max_heap.pop();
      }
    } else {
      max_heap.push(x);
      min_heap.push(max_heap.top());
      max_heap.pop();
    }

    ++size;
  }

  double median() {
    if (size % 2 == 0) {
      return (max_heap.top() + min_heap.top()) / 2.0;
    }

    return max_heap.top();
  }
};

int main() {
  int array[] = { 42, -1, 2, 0, 3, 4, 30, 23 };
  std::cout << kth_smallest(array, 8, 3) << '\n';
  std::cout << kth_smallest_with_max_heap(array, 8, 3) << '\n';

  Median m;
  for (int x : array) {
    m.insert(x);
  }

  std::cout << m.median() << '\n';

  return 0;
}
