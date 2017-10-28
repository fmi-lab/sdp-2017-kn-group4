#include <queue.h>

bool Queue::empty() const {
  return enqueue_stack.empty() && dequeue_stack.empty();
}

size_t Queue::size() const {
  return enqueue_stack.size() + dequeue_stack.size();
}

int Queue::front() {
  if (dequeue_stack.empty()) {
    transfer();
  }

  return dequeue_stack.top();
}

void Queue::enqueue(int element) {
  enqueue_stack.push(element);
}

int Queue::dequeue() {
  if (dequeue_stack.empty()) {
    transfer();
  }

  int popped = dequeue_stack.top();
  dequeue_stack.pop();
  return popped;
}

void Queue::transfer() {
  while (!enqueue_stack.empty()) {
    dequeue_stack.push(enqueue_stack.top());
    enqueue_stack.pop();
  }
}
