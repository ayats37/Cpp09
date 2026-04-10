#include "RPN.hpp"

int rpn(char **argv){
  std::stack<int> st;
  std::string expr = argv[1];
  for (size_t i = 0; i < expr.size(); i++){
    if (expr[i] == ' ')
      continue;
    if (isdigit(expr[i]))
      st.push(expr[i] - '0');
    else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/'){
      if (st.size() < 2){
        std::cerr << "Error" << std::endl;
        return 1;
      }
      int b = st.top(); st.pop();
      int a = st.top(); st.pop();
      if (expr[i] == '+') st.push(a + b);
      else if (expr[i] == '-') st.push(a - b);
      else if (expr[i] == '*') st.push(a * b);
      else{
        if (b == 0){
          std::cerr << "Error" << std::endl;
          return 1;
        }
        st.push(a / b);
      }
    }
    else{
      std::cerr << "Error" << std::endl;
      return 1;
    }
  }
  if (st.size() != 1){
    std::cerr << "Error" << std::endl;
    return 1;
  }
  std::cout << st.top() << std::endl;
  return 0;
}