#ifndef CALCULATOR_CALCULATOR_H
#define CALCULATOR_CALCULATOR_H

#include <stack>

class Queue {
  std::stack<int> enqueue_stack;
  std::stack<int> dequeue_stack;

public:

  bool empty() const;

  size_t size() const;

  int front() const;

  void enqueue(int element);

  int dequeue();
};

#endif
