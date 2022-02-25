#include <iostream>

typedef double(*TwoIntsToDouble)(int numerator, int denominator); 

double apply(TwoIntsToDouble f, int int1, int int2) {
  return f(int1, int2);
}

double divide(int int1, int int2) {
  return static_cast<double>(int1)/int2;
}

double add(int int1, int int2) {
  return static_cast<double>(int1)/int2;
}

class DivideObj {
public:
  double operator()(int nom, int denom) {return double(nom)/denom;}
};

template <typename Operand1, typename Operand2, typename OperatorType>
class BinaryOperator {
  Operand1 op1;
  Operand2 op2;
  OperatorType oper;
  public:
  BinaryOperator(Operand1 o1, Operand2 o2) : op1(o1), op2(o2) {}
  void setOperator(OperatorType o) {
    oper = o;
  }
  auto operator()() {
    auto ret = [this]() -> auto { return oper(op1, op2); };
    return ret;
  }
};

int main() {
  std::cout << DivideObj()(6, 2) << std::endl;
  auto divideLambda = [](int nom, int denom) -> double { return static_cast<double>(nom)/denom; };
  int two = 2;
  std::cout << apply(divideLambda, 5, 3) << std::endl; 
  BinaryOperator<int, int, DivideObj> binop(10, 4);
  binop.setOperator(DivideObj());
  std::cout << binop()() << std::endl;
  return 0;
}
