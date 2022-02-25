#include <iostream>
#include <functional>

using namespace std;

auto& returnRef(int& p) { return p; }

struct MyStruct {
  int d;
  MyStruct(int d) : d(d) {}
};

int main() {
  int a = 10;
  decltype(a) b;
  cout << "decltype(a) is " << typeid(b).name() << "\n";

  decltype(returnRef(a)) c = b;
  cout << a << "\t" << &b << "\t" << c << "\n";

  MyStruct* ms = new MyStruct(5);
  decltype(ms->d) e1;
  cout << e1 << "\n";
  decltype((ms->d)) e2 = ms->d;
  cout << e2 << "\n";
  delete ms;
  return 0;
}
