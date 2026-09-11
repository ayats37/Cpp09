#include "RPN.hpp"

RPN::RPN() {}
RPN::RPN(const RPN& other) { *this = other; }
RPN& RPN::operator=(const RPN& other) {
  if (this != &other)
    _stack = other._stack;
  return *this;
}
RPN::~RPN() {}

void RPN::applyOperator(char op){
  if (_stack.size() < 2)
    throw std::runtime_error("Error");
  int b = _stack.top(); _stack.pop();
  int a = _stack.top(); _stack.pop();
  if (op == '+') _stack.push(a + b);
  else if (op == '-') _stack.push(a - b);
  else if (op == '*') _stack.push(a * b);
  else if (op == '/'){
    if (b == 0)
      throw std::runtime_error("Error");
    _stack.push(a / b);
  }
}
int RPN::evaluate(const std::string &expr){
  while (!_stack.empty()) _stack.pop();
  for (size_t i = 0; i < expr.size(); i++){
    if (expr[i] == ' ')
      continue;
    if (isdigit(expr[i]))
      _stack.push(expr[i] - '0');
    else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/'){
      applyOperator(expr[i]);
    }
    else
      throw std::runtime_error("Error");
  }
  if (_stack.size() != 1)
    throw std::runtime_error("Error");
  return _stack.top();
}