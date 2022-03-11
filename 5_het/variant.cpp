#include <variant>
#include <iostream>

class A {
  int x;
  public:
  A(int a) : x(a) {}
  void print() { std::cout << "my value is " << x << std::endl; }
};

int variantPelda() {
  std::variant<A, double, int, std::string> var(A(4)); // A nem lehet elol mert nincs default konstruktora!
  A x = std::get<0>(var);
  A x2 = std::get<A>(var); // ez is mukodik
  x.print();
  x2.print();
  try {
    A y = std::get<2>(var);
    y.print();
  } catch (std::bad_variant_access& e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}

struct Visitor {
  void operator()(int n) { std::cout << "int\n"; }
  void operator()(double n) { std::cout << "double\n"; }
};

void visitFunc() {
  std::variant<int, double> number = 42;
  Visitor v;
  std::visit(v, number);
  number = 3.14;
  std::visit(v, number);
}

int main() {
  visitFunc();
  return 0;
}
