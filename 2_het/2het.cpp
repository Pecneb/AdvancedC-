#include <iostream>

using namespace std;

/* Reifikalt fuggvenyek */
int aFunc(int n) {

  return n + 1;

}

int bFunc(int n) {

  return n * 2;

}

// A function can take a function as an argument.
int xFunc(int(*fp)(int), int n) {

  return fp(n);
}

// Define a function that takes an int as argument
typedef int(*function_ptr)(int);
int myFunc(int x) {

  return x*3;

}

class ConvertibleToFunctionPointer {

  int num_times_called;

  public:

  ConvertibleToFunctionPointer() : num_times_called(0) {}

  operator function_ptr() {

    num_times_called++;

    cout << "called " << num_times_called << " times!" << endl;

    return myFunc;

  }
};

int main() {
  cout << xFunc(aFunc, 20) << "\n";
  cout << xFunc(bFunc, 20) << "\n";

  ConvertibleToFunctionPointer cfp;
  cfp(2);
  cfp(2);
  cfp(2);
  return 0;
}
