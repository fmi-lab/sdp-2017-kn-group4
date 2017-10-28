#ifndef QUEUE_QUEUE_H
#define QUEUE_QUEUE_H

#include <stack>

class Queue {
  std::stack<int> enqueue_stack;
  std::stack<int> dequeue_stack;

  void transfer();

public:

  bool empty() const;

  size_t size() const;

  int front();

  void enqueue(int element);

  int dequeue();
};

#endif
