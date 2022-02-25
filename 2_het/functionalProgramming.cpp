#include <iostream>
#include <functional>

using namespace std;

/* a functional programming alapjait mutatja be,
 * amikor egy fuggveny pl egy masik fuggvenyt var
 * argumentumkent es annak a fv-nek a visszateresi
 * erteket kell visszaadnia */

template <typename Function, typename Object>
decltype(auto) applyFnToObject(Function func, Object&& obj) {
  return func(forward<Object>(obj));
}

class AddTwo {
public:
  int operator()(int input) { return input + 2; }
};

class AddTwoRightRef {
  int value;
public:
  AddTwoRightRef() { value = 0; }
  int operator()(int&& input) { 
    value = input + 2;
    return value;
  }
};

int main() {
  cout << applyFnToObject(AddTwo(), 5) << "\n";
  int x = 20;
  cout << applyFnToObject(AddTwoRightRef(), move(x)) << "\n";
  return 0;
}
