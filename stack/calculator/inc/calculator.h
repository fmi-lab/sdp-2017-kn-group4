#ifndef CALCULATOR_CALCULATOR_H
#define CALCULATOR_CALCULATOR_H

#include <functional>
#include <stack>

class Calculator {
  double state;

  std::stack<double> undo_stack;
  std::stack<double> redo_stack;

public:

  Calculator(double initial_state = 0);

  double get_state() const;

  double apply_operation(std::function<double (double, double)> operation,
                        double second_operand);

  double undo(int count);

  double redo(int count);
};

#endif
