#include <optional>
#include <cstdio>

class A {
  int x;
public:
  A(int a) : x(a) {}
  void print() {
    printf("my value is %d\n", x);
  }
};

int main() {
  A a1{ 5 };
  std::optional<A> perhapsa1;
  std::optional<A> definitelya1{ a1 };
  if (!perhapsa1) {  printf("perhapsa1 has no value\n"); }
  if (definitelya1) { // definitelya1.has_value() is jo
    definitelya1.value().print();
    (*definitelya1).print(); // ez a 2 is mukodik...
    definitelya1->print();
  }
  return 0;
}
