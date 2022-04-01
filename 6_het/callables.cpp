#include <iostream>

int firstFunc ( int (*fptr) (int), int x) { return fptr(x); } // function expects a function and an int, then calls the function with the int

typedef int(*function_ptr)(int); // function pointer type definiton

int myFunc(int x) { return x * 3; } // this is a function_ptr type function, becouse it expects an int as argument and returns an int

int callFunc(function_ptr f, int x) { return f(x); }

int main() {
  int first = firstFunc([](int y) -> int { return y * 5; }, 5); // firstFunc() that waits a function and an int an arg, called with a lambda func
  std::cout << "firstFunc called with lambda: " << first << std::endl;

  int second = firstFunc(myFunc, 5); // now it is called with a function "myFunc()" that waits an int and returns an int
  std::cout << "firstFunc called with myFunc(): " << second << std::endl;

  return 0;
}
