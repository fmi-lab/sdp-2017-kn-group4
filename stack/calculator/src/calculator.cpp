#include "calculator.h"

Calculator::Calculator(double initial_state): state(initial_state) {}

double Calculator::get_state() const {
  return state;
}

double Calculator::apply_operation(
  std::function<double(double, double)> operation, double second_operand) {
  undo_stack.push(state);
  redo_stack = std::stack<double>();
  state = operation(state, second_operand);
  return state;
}

double Calculator::undo(int count) {
  if (undo_stack.empty()) {
    return state;
  }

  while (!undo_stack.empty() && count > 0) {
    redo_stack.push(state);
    state = undo_stack.top();
    undo_stack.pop();
    --count;
  }

  return state;
}

double Calculator::redo(int count) {
  if (redo_stack.empty()) {
    return state;
  }

  while(!redo_stack.empty() && count > 0) {
    undo_stack.push(state);
    state = redo_stack.top();
    redo_stack.pop();
    --count;
  }

  return state;
}
